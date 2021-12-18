/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include "Convolver.hpp"
#include "cores/arithmetic-exact.hpp"

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
template <typename T, int K, class ADD = arithmetic::exact::Add<T>,
          class MULT = arithmetic::exact::Mult<T>>
class Exact : public Convolver<T, K, ADD, MULT> {
 public:
  /**
   * Execute the implementation
   * @param window input window to convolve with the kernel
   * @param kernel kernel to convolve with
   * @param output output window
   */
  virtual void Execute(
      const T window[Convolver<T, K, ADD, MULT>::windowsize]
                    [Convolver<T, K, ADD, MULT>::windowsize],
      const T kernel[Convolver<T, K, ADD, MULT>::kernelsize]
                    [Convolver<T, K, ADD, MULT>::kernelsize],
      T output[Convolver<T, K, ADD, MULT>::outputsize]
              [Convolver<T, K, ADD, MULT>::outputsize]) override;

 private:
  ADD add_{};
  MULT mult_{};
};

template <typename T, int K, class ADD, class MULT>
inline void Exact<T, K, ADD, MULT>::Execute(
    const T window[Convolver<T, K, ADD, MULT>::windowsize]
                  [Convolver<T, K, ADD, MULT>::windowsize],
    const T kernel[Convolver<T, K, ADD, MULT>::kernelsize]
                  [Convolver<T, K, ADD, MULT>::kernelsize],
    T output[Convolver<T, K, ADD, MULT>::outputsize]
            [Convolver<T, K, ADD, MULT>::outputsize]) {
  T sum = 0;
space_exact_execute_i:
  for (int i{0}; i < Convolver<T, K, ADD, MULT>::outputsize; ++i) {
  space_exact_execute_j:
    for (int j{0}; j < Convolver<T, K, ADD, MULT>::outputsize; ++j) {
    space_exact_execute_e:
      for (int e{0}; e < Convolver<T, K, ADD, MULT>::kernelsize; ++e) {
      space_exact_execute_r:
        for (int r{0}; r < Convolver<T, K, ADD, MULT>::kernelsize; ++r) {
          sum = add_(sum, mult_(kernel[e][r], window[i + e][j + r]));
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
