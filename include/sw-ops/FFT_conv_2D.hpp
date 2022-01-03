/*
 * Copyright 2021
 * Author: Alejandro Rodriguez Figueroa <alejandrorf@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <complex>
#include <iostream>
#include <valarray>
#include "FFT_2D.hpp"
#include "IFFT_2D.hpp"
#include "PaddKernel_FFT.hpp"

#pragma once

/**
 * @brief Matrix fft convolution for array
 * It performs a lineal fft for array of complex numbers.
 * @param input input matrix
 * @param kernel input matrix kernel
 * @param N number of columns
 * @param M number of rows
 * @param K size of the kernel
 */

namespace ama {
namespace sw {

// template <typename Complex, typename CArray, int M, int N>

template <typename T>
using Complex = std::complex<T>;

template <typename T>
using CArray = std::valarray<Complex<T>>;

template <typename T, int M, int N, int K>

void fft_conv_2D(Complex<T> input[M][N], const T kernel[K][K]) {
  ama::sw::fft_2D<T, M, N>(input);

  Complex<T> b[M][N] = {0};
  Complex<T> a[M][N] = {0};

  ama::sw::paddkernel_FFT<T, M, N, K>(kernel, b);

  ama::sw::fft_2D<T, M, N>(b);

  int i_mid = (M / 2) - 1;
  int j_mid = (M / 2) - 1;

  for (int i{0}; i < M; ++i) {
    for (int j{0}; j < N; ++j) {
      input[i][j] = input[i][j] * b[i][j];
    }
  }

  ama::sw::ifft_2D<T, M, N>(input);

  for (int i{0}; i < M; ++i) {
    for (int j{0}; j < N; ++j) {
      a[i][j] = input[i][j];
    }
  }

  for (int i{0}; i < M; ++i) {
    for (int j{0}; j < N; ++j) {
      if (i <= i_mid && j <= j_mid) {
        input[i + i_mid][j + j_mid] = a[i][j].real();
      } else if (i < i_mid && j > j_mid) {
        input[i + i_mid][j - j_mid] = a[i][j].real();
      } else if (i >= i_mid && j <= j_mid) {
        input[i - i_mid][j + j_mid] = a[i][j].real();
      } else if (i > i_mid && j > j_mid) {
        input[i - i_mid][j - j_mid] = a[i][j].real();
      }
    }
  }
}
}  // namespace sw
}  // namespace ama