/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include "Convolver.hpp"

namespace ama {
namespace hw {
namespace space {
namespace core {

using namespace ama::hw;

/**
 * Exact space convolution functor class
 * @tparam T datatype
 * @tparam K kernel size
 */
template <typename T, int K>
class Exact : public Convolver<T, K> {
 public:
  /**
   * Execute the exact implementation
   * @param window input window to convolve with the kernel
   * @param kernel kernel to convolve with
   * @param output output window
   */
  virtual void Execute(
      const T window[Convolver<T, K>::windowsize][Convolver<T, K>::windowsize],
      const T kernel[Convolver<T, K>::kernelsize][Convolver<T, K>::kernelsize],
      T output[Convolver<T, K>::outputsize][Convolver<T, K>::outputsize])
      override;
};

template <typename T>
T mult(const T lhs, const T rhs) {
  return lhs * rhs;
}

template <typename T, int K>
inline void Exact<T, K>::Execute(
    const T window[Convolver<T, K>::windowsize][Convolver<T, K>::windowsize],
    const T kernel[Convolver<T, K>::kernelsize][Convolver<T, K>::kernelsize],
    T output[Convolver<T, K>::outputsize][Convolver<T, K>::outputsize]) {
  T sum = 0;
space_exact_execute_i:
  for (int i{0}; i < Convolver<T, K>::outputsize; ++i) {
  space_exact_execute_j:
    for (int j{0}; j < Convolver<T, K>::outputsize; ++j) {
    space_exact_execute_e:
      for (int e{0}; e < Convolver<T, K>::kernelsize; ++e) {
      space_exact_execute_r:
        for (int r{0}; r < Convolver<T, K>::kernelsize; ++r) {
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
