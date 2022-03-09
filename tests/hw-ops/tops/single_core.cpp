/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include "single_core.hpp"

#ifndef Q_CONV_CORE
#define Q_CONV_CORE Spatial
#endif

#if Q_CONV_CORE == Winograd
#if Q_K == 3
#define CONV_CORE Winograd
#elif Q_K == 5
#define CONV_CORE Winograd5
#elif Q_K == 7
#define CONV_CORE Winograd7
#endif
#else
#define CONV_CORE Q_CONV_CORE
#endif

#define ENGINE(x) ama::hw::convolvers::x<DataType, Q_K, Q_O>{};

/* The convolution happens in row-major but it is transferred by columns */
void single_core_top_accel(DataType input[kWindowSize][kWindowSize],
                           DataType kernel[kKernelSize][kKernelSize],
                           DataType output[kOutputSize][kOutputSize]) {
#pragma HLS INLINE
  auto engine = ENGINE(CONV_CORE);
  engine.Execute(input, kernel, output);
}
