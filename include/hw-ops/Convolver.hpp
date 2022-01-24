/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include "cores/arithmetic-exact.hpp"

namespace ama {
namespace hw {

/**
 * Convolver template class
 * It defines the interface for any convolution engine. It also defines
 * the window sizes as a function of the kernel size.
 * @tparam T datatype to work with.
 * @tparam K kernel side size
 * @tparam ADD add functor
 * @tparam ADD mult functor
 */
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

/**
 * Begin of the metaprogramming loop
 * This struct will recurse until having a termination as a
 * specialisation.
 * @tparam N current iteration. In the first, it is equal to NT
 * @tparam NT total number of iterations
 * @tparam ENGINE class/module to iterate
 */
template <int N, int NT, class ENGINE>
struct ParallelConvolver {
  /**
   * Execute method
   * It exposes the execution static to interact with the ENGINE
   * FIXME: generalise for K != 3
   * @param input input window
   * @param kernel kernel to convolve with
   * @param output output window
   */
  static void Execute(
      DataType input[NT * ENGINE::outputsize + 2][ENGINE::windowsize],
      DataType kernel[ENGINE::kernelsize][ENGINE::kernelsize],
      DataType output[NT * ENGINE::outputsize][ENGINE::outputsize]) {
#pragma HLS INLINE /* Important! Inlining the execution allows parallelism */
    /* Execute PE */
    ENGINE op{};
    op.Execute(&input[2 * (N - 1)], kernel, &output[2 * (N - 1)]);

    /* Continue Loop - The next i = i - 1 */
    ParallelConvolver<(N - 1), NT, ENGINE>::Execute(input, kernel, output);
  }
};

/**
 * End of the metaprogramming loop
 */
template <int NT, class ENGINE>
struct ParallelConvolver<0, NT, ENGINE> {
  /**
   * Execute method
   * It exposes the execution static to interact with the ENGINE
   * @param input input window
   * @param kernel kernel to convolve with
   * @param output output window
   */
  static void Execute(
      DataType input[NT * ENGINE::outputsize + 2][ENGINE::windowsize],
      DataType kernel[ENGINE::kernelsize][ENGINE::kernelsize],
      DataType output[NT * ENGINE::outputsize][ENGINE::outputsize]) {
#pragma HLS INLINE /* Important! Inlining the execution allows parallelism */
    /* Do Nothing (terminate loop) */
  }
};

} /* namespace hw */
} /* namespace ama */
