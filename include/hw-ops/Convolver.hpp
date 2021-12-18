/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include "cores/arithmetic-exact.hpp"

namespace ama {
namespace hw {

template <typename T, int K, class ADD = arithmetic::exact::Add<T>,
          class MULT = arithmetic::exact::Mult<T>>
class Convolver {
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
  virtual void Execute(const T window[windowsize][windowsize],
                       const T kernel[kernelsize][kernelsize],
                       T output[outputsize][outputsize]) {}
};

} /* namespace hw */
} /* namespace ama */
