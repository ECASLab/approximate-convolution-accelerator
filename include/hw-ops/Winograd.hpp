/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

namespace ama {
namespace hw {
namespace winograd {
namespace core {

template <typename T, int K>
class Exact {
 public:
  /*
   * Define some useful variables for implementation purposes
   * This may change according to the kernel. In the meantime
   * it is assumed to be K = 3
   * FIXME: extend to kernels of different sizes
   */
  static const int kernelsize = K;
  static const int windowsize = K + 1;
  static const int outputsize = K - 1;

  /**
   * Execute the exact implementation
   * @param window input window to convolve with the kernel
   * @param window input window to convolve with the kernel
   */
  void Execute(const T window[windowsize][windowsize],
               const T kernel[kernelsize][kernelsize],
               T output[outputsize][outputsize]) {
    /* Unroll variables to ease the access*/
    const T* window_u = window[0];
    const T* kernel_u = kernel[0];

    /* Execute - Simplied using sympy */
    output[0][0] = kernel_u[0] * window_u[0] + kernel_u[1] * window_u[1] +
                   kernel_u[2] * window_u[2] + kernel_u[3] * window_u[4] +
                   kernel_u[4] * window_u[5] + kernel_u[5] * window_u[6] +
                   kernel_u[6] * window_u[8] + kernel_u[7] * window_u[9] +
                   kernel_u[8] * window_u[10];
    output[0][1] = kernel_u[0] * window_u[1] + kernel_u[1] * window_u[2] +
                   kernel_u[2] * window_u[3] + kernel_u[3] * window_u[5] +
                   kernel_u[4] * window_u[6] + kernel_u[5] * window_u[7] +
                   kernel_u[6] * window_u[9] + kernel_u[7] * window_u[10] +
                   kernel_u[8] * window_u[11];
    output[1][0] = kernel_u[0] * window_u[4] + kernel_u[1] * window_u[5] +
                   kernel_u[2] * window_u[6] + kernel_u[3] * window_u[8] +
                   kernel_u[4] * window_u[9] + kernel_u[5] * window_u[10] +
                   kernel_u[6] * window_u[12] + kernel_u[7] * window_u[13] +
                   kernel_u[8] * window_u[14];
    output[1][1] = kernel_u[0] * window_u[5] + kernel_u[1] * window_u[6] +
                   kernel_u[2] * window_u[7] + kernel_u[3] * window_u[9] +
                   kernel_u[4] * window_u[10] + kernel_u[5] * window_u[11] +
                   kernel_u[6] * window_u[13] + kernel_u[7] * window_u[14] +
                   kernel_u[8] * window_u[15];
  }
};

} /* namespace core */
} /* namespace winograd */
} /* namespace hw */
} /* namespace ama */
