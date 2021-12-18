/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

namespace ama {
namespace hw {
namespace space {
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
   * @param kernel kernel to convolve with
   * @param output output window
   */
  void Execute(const T window[windowsize][windowsize],
               const T kernel[kernelsize][kernelsize],
               T output[outputsize][outputsize]);
};

template <typename T>
T mult(const T lhs, const T rhs) {
  return lhs * rhs;
}

template <typename T, int K>
inline void Exact<T, K>::Execute(
    const T window[Exact<T, K>::windowsize][Exact<T, K>::windowsize],
    const T kernel[Exact<T, K>::kernelsize][Exact<T, K>::kernelsize],
    T output[Exact<T, K>::outputsize][Exact<T, K>::outputsize]) {
  T sum = 0;
space_exact_execute_i:
  for (int i{0}; i < outputsize; ++i) {
  space_exact_execute_j:
    for (int j{0}; j < outputsize; ++j) {
    space_exact_execute_e:
      for (int e{0}; e < kernelsize; ++e) {
      space_exact_execute_r:
        for (int r{0}; r < kernelsize; ++r) {
          sum += mult(kernel[e][r], window[i + e][j + r]);
        }
      }
      output[i][j] = sum;
      sum = 0;
    }
  }
}

} /* namespace core */
} /* namespace space */
} /* namespace hw */
} /* namespace ama */
