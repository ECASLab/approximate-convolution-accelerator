/*
 * Copyright 2021
 * Author: Alejandro Rodriguez Figueroa <alejandrorf@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

namespace ama {
namespace sw {

template <typename T>
using Complex = std::complex<T>;

template <typename T>
using CArray = std::valarray<Complex<T>>;

template <typename T, int M, int N, int k>

/**
 * @brief Matrix padding
 * It performs the padding on a matrix for a kernel size k.
 * @param input_kernel Matrix original kernel
 * @param output_image kernel with the padding applied
 */

void paddkernel_FFT(const T input_kernel[k][k], Complex<T> output_image[M][N]) {
  int start[2] = {0};
  if (k == 3) {
    start[0] = (M / 2) - 2;
    start[1] = (N / 2) - 2;
  } else if (k == 5) {
    start[0] = (M / 2) - 3;
    start[1] = (N / 2) - 3;
  } else {
    start[0] = (M / 2) - 4;
    start[1] = (N / 2) - 4;
  }

  for (int i{0}; i < k; ++i) {
    for (int j{0}; j < k; ++j) {
      output_image[start[0] + i][start[1] + j] = input_kernel[i][j];
    }
  }
}
}  // namespace sw
}  // namespace ama
