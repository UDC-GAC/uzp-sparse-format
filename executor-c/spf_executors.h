/*
 * spf_executors.h: This file is part of the SPF project.
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

#ifndef _SPF_EXECUTORS_H
# define _SPF_EXECUTORS_H

#include <spf_structure.h>

extern
int
spf_executors_spf_matrix_dense_vector_product(s_spf_structure_t* restrict spf_matrix,
					      const void* const restrict x,
					      void* restrict y,
					      int ncols,
					      int nrows,
					      int data_is_float, 
						  int nThreads);

extern
int
spf_executors_spf_matrix_dense_matrix_product(s_spf_structure_t* restrict spf_matrix,
					      void* restrict B, // matrix
					      void* restrict C, // matrix
					      int ni,
					      int nj,
					      int nk,
					      int data_is_float,
					      int TJ);



#endif // !_SPF_EXECUTORS_H
