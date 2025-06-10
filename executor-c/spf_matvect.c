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


int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: spmv_spf <SPF file>\n");
        exit(0);
    }

    int debug = 0;
    int nthread = 0;
    int data_is_float = 0;
    int print_matrix_summary = debug;
    int print_matrix_structure = 0 || (debug > 1);

    char* rbpath = NULL;
    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "-float")) {
            data_is_float = 1;
        } else if (!strcmp(argv[i], "-stats")) {
            print_matrix_summary = 1;
        } else if (!strcmp(argv[i], "-structure")) {
            print_matrix_structure = 1;
        } else if (!strcmp(argv[i], "-nthread")) {
            if (i + 1 < argc) {
                nthread = atoi(argv[i + 1]);
                i++;
            } else {
                fprintf(stderr, "Error: Missing value for -nthread\n");
                exit(EXIT_FAILURE);
            }
        } else {
            if (rbpath == NULL) {
                rbpath = argv[i];
            } else {
                fprintf(stderr, "[ERROR] Unsupported argument %s\n", argv[i]);
                usage(argv);
            }
        }
    }

    if (!rbpath) {
        usage(argv);
    }

  // Load the matrix.
  s_spf_structure_t* spf_mat = spf_matrix_read_from_file (rbpath);
  if (! spf_mat)
    exit (1);

  // Convert data to float, if asked.
  if (data_is_float)
    spf_matrix_convert_data_to_float (spf_mat);

  if (print_matrix_summary)
    spf_matrix_print_summary (stdout, spf_mat);
  if (print_matrix_structure)
    spf_matrix_print_structure (stdout, spf_mat);
  if (debug > 10)
    spf_matrix_print (spf_mat);

  // Set the total number of flops.
#ifdef POLYBENCH_GFLOPS
  polybench_program_total_flops = spf_mat->matrix_description.nnz * 2;
#endif

  // Allocate and initialize x, y to fake values.
  int ncols = spf_mat->matrix_description.ncols;
  int nrows = spf_mat->matrix_description.intnrow;
  void* x;
  void* y;
  if (! data_is_float)
    {
      
      x = (double*) polybench_alloc_data (ncols, sizeof(double));
      y = (double*) polybench_alloc_data (nrows, sizeof(double));
      for (int i = 0; i < nrows; ++i)
	((double*)y)[i] = 0;
      for (int i = 0; i < ncols; i++) {
	((double*)x)[i] = (double)(i % ncols) / ncols;
      }
    }
  else
    {
      x = (float*) polybench_alloc_data (ncols, sizeof(float));
      y = (float*) polybench_alloc_data (nrows, sizeof(float));
      for (int i = 0; i < nrows; ++i)
	((float*)y)[i] = 0;
      for (int i = 0; i < ncols; i++) {
	((float*)x)[i] = (float)(i % ncols) / ncols;
      }
    }

  // Repeat the spmv computation, and monitor it with polybench,
  // clearing cache between each repetition.
  for (int repeat = 0; repeat < NB_REPEATS_EXPERIMENT_COLD_CACHE; ++repeat)
    {
      polybench_start_instruments;
      spf_executors_spf_matrix_dense_vector_product (spf_mat, x, y,
						     ncols, nrows,
						     data_is_float, nthread);
      polybench_stop_instruments;
      polybench_print_instruments;
    }

  // Dump the output vector.
  if (debug > 10)
    {
      if (data_is_float)
	{
	  for (int i = 0; i < nrows; i++)
	    printf ("%f ", ((float*)y)[i]);
	}
      else
	{
	  for (int i = 0; i < nrows; i++)
	    printf ("%f ", ((double*)y)[i]);
	}
      printf ("\n");
    }

  return 0;
}
