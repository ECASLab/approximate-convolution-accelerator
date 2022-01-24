/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include "convolver_vector.hpp"

#include "convolution.hpp"

/* The convolution happens in row-major but it is transferred by columns */
void convolver_vector_top_accel(DataType input[Q_ACCEL * 2 + 2][4],
                                DataType kernel[Q_K][Q_K],
                                DataType output[Q_ACCEL * 2][2]) {
#pragma HLS INLINE
  using Engine = ama::hw::convolvers::Spatial<DataType, Q_K>;
  ama::hw::ParallelConvolver<Q_ACCEL, Q_ACCEL, Engine>::Execute(input, kernel,
                                                                output);
}
