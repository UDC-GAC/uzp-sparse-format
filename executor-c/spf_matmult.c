/*
 * spf_matvect.c: This file is part of the SPF project.
 *
 * SPF: the Sparse Polyhedral Format
 *
 * Copyright (C) 2023 UDC and CSU
 *
 * This program can be redistributed and/or modified under the terms
 * of the license specified in the LICENSE.txt file at the root of the
 * project.
 *
 * Contact: Gabriel Rodriguez Alvarez <gabriel.rodriguez@udc.es>
 *          Louis-Noel Pouchet <pouchet@colostate.edu>
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <sys/mman.h>
#include <assert.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#ifdef _OPENMP
# include <omp.h>
#endif

#include <spf_structure.h>
#include <spf_executors.h>

#include <polybench.h>

#ifndef NB_REPEATS_EXPERIMENT_COLD_CACHE
# define NB_REPEATS_EXPERIMENT_COLD_CACHE 5
#endif

static void usage(char** argv)
{
  fprintf (stderr, "Usage: %s [-float,-stats] <spf_matrix.spfdata>\n", argv[0]);
  exit (1);
}


int main(int argc, char** argv)
{

  if( argc < 2 ) {
      printf( "Usage: spmv_spf <SPF file>\n" );
      exit(0);
  }

  int debug = 0;

  int data_is_float = 0;
  int print_matrix_summary = debug;
  int print_matrix_structure = 0 || (debug > 1);
  int TJ = 0;
  int cache_line_alignment_factor = 16;
  int nj = 0;

  char* rbpath = NULL;
  for (int i = 1; i < argc; ++i)
    {
      if (! strcmp (argv[i], "-float"))
	data_is_float = 1;
      else if (! strcmp (argv[i], "-stats"))
	print_matrix_summary = 1;
      else if (! strcmp (argv[i], "-structure"))
	print_matrix_structure = 1;
      else if (! strncmp (argv[i], "-nj=", strlen ("-nj=")))
	{
	  nj = atoi (argv[i] + 4);
	}
      else if (! strncmp (argv[i], "-TJ=", strlen ("-TJ=")))
	{
	  TJ = atoi (argv[i] + 4);
	}
      else if (! strncmp (argv[i], "-cl=", strlen ("-cl=")))
	{
	  cache_line_alignment_factor = atoi (argv[i] + 4);
	}
      else
	{
	  if (rbpath == NULL)
	    rbpath = argv[i];
	  else
	    {
	      fprintf (stderr, "[ERROR] Unsupported argument %s\n",
		       argv[i]);
	      usage (argv);
	    }
	}
    }

  if (! rbpath)
    usage (argv);

  // Load the matrix.
  s_spf_structure_t* spf_mat = spf_matrix_read_from_file (rbpath);
  if (! spf_mat)
    {
      fprintf (stderr, "[ERROR] Cannot load %s\n", rbpath);
      usage (argv);
    }

  // Convert data to float, if asked.
  if (data_is_float)
    spf_matrix_convert_data_to_float (spf_mat);

  if (print_matrix_summary)
    spf_matrix_print_summary (stdout, spf_mat);
  if (print_matrix_structure)
    spf_matrix_print_structure (stdout, spf_mat);
  if (debug > 10)
    spf_matrix_print (spf_mat);

  // Allocate and initialize x, y to fake values.
  int ncols = spf_mat->matrix_description.ncols;
  int nrows = spf_mat->matrix_description.intnrow;

  int ni = nrows;
  int nk = ncols;

  // Set dense matrix size.
  if (nj == 0)
    {
      nj = ni;
      if (ni > 10000)
	nj = (int)sqrt (ni);
    }

  // Default tile size == nj / no tiling.
  // Other good overall value: 64.
  if (TJ == 0)
    TJ = nj;

  // Adjust TJ to the number of threads.
#ifdef _OPENMP
  int nbthreads = omp_get_max_threads ();
  if (TJ == nj)
    {
      TJ = ceil((float)TJ / (float)nbthreads);
      // Round to multiple of 16, hopefully avoiding some false sharing...
      TJ += (cache_line_alignment_factor - TJ % cache_line_alignment_factor);
      printf ("[INFO] Adjusted TJ = %d, for %d threads\n", TJ, nbthreads);
    }
#endif


  // Set the total number of flops.
#ifdef POLYBENCH_GFLOPS
  polybench_program_total_flops =
    spf_mat->matrix_description.nnz * 2 * (double)nj;
#endif

  if (print_matrix_summary)
    printf ("C(dense) = %d x %d, A(spf) = %d x %d with %d nnz, B(dense) = %d x %d\n", ni, nj, nrows, ncols, spf_mat->matrix_description.nnz, nk, nj);

  void* Cptr;
  void* Bptr;
  if (! data_is_float)
    {
      POLYBENCH_2D_ARRAY_DECL(C,double,ni,nj,ni,nj);
      POLYBENCH_2D_ARRAY_DECL(B,double,nk,nj,nk,nj);

      for (int i = 0; i < ni; ++i)
	for (int j = 0; j < nj; ++j)
	  (POLYBENCH_ARRAY(C))[i][j] = 0;

      for (int i = 0; i < nk; ++i)
	for (int j = 0; j < nj; ++j)
	  (POLYBENCH_ARRAY(B))[i][j] = (i % nj) / ni;
      Cptr = C;
      Bptr = B;
    }
  else
    {
      POLYBENCH_2D_ARRAY_DECL(C,float,ni,nj,ni,nj);
      POLYBENCH_2D_ARRAY_DECL(B,float,nk,nj,nk,nj);
      for (int i = 0; i < ni; ++i)
	for (int j = 0; j < nj; ++j)
	  (POLYBENCH_ARRAY(C))[i][j] = 0;
      for (int i = 0; i < nk; ++i)
	for (int j = 0; j < nj; ++j)
	  (POLYBENCH_ARRAY(B))[i][j] = (i % nj) / ni;
      Cptr = C;
      Bptr = B;
    }

  // Repeat the spmv computation, and monitor it with polybench,
  // clearing cache between each repetition.
  for (int repeat = 0; repeat < NB_REPEATS_EXPERIMENT_COLD_CACHE; ++repeat)
    {
      polybench_start_instruments;
      spf_executors_spf_matrix_dense_matrix_product (spf_mat, Bptr, Cptr,
  						     ni, nj, nk,
  						     data_is_float, TJ);
      polybench_stop_instruments;
      polybench_print_instruments;
    }

  // Dump the output vector.
  if (debug > 10)
    {
      if (data_is_float)
	for (int i = 0; i < ni; i++)
	  for (int j = 0; j < nj; j++)
	    printf ("%f ", ((float*)Cptr)[i * ni + j]);
      else
	for (int i = 0; i < ni; i++)
	  for (int j = 0; j < nj; j++)
	    printf ("%f ", ((double*)Cptr)[i * ni + j]);
      printf ("\n");
    }

  return 0;
}
