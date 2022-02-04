/*
 * Copyright 2021
 * Author: Alejandro Rodriguez Figueroa <alejandrorf@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <complex>
#include <iostream>
#include <valarray>
#include "FFT.hpp"
#pragma once
#include "../utils/FFT_header.hpp"


namespace ama {
namespace sw {

/**
 * @brief Matrix fft convolution for array
 * It performs a lineal fft for array of complex numbers.
 * @param input input matrix
 * @param N number of columns
 * @param M number of rows
 */

template <typename T, int M, int N>

void fft_2D(Complex<T> input[M][N]) {
  Complex<T> input_arr[M] = {0};
  // Row FFT
  for (int i{0}; i < M; ++i) {
    for (int j{0}; j < N; ++j) {
      input_arr[j] = input[i][j];
    }
    CArray<T> data(input_arr, N);
    ama::sw::fft<T>(data);
    for (int j{0}; j < N; ++j) {
      input[i][j] = data[j];
    }
  }
  // Columns FFT
  for (int i{0}; i < N; ++i) {
    for (int j{0}; j < M; ++j) {
      input_arr[j] = input[j][i];
    }
    CArray<T> data(input_arr, M);
    ama::sw::fft<T>(data);
    for (int j{0}; j < M; ++j) {
      input[j][i] = data[j];
    }
  }
}
}  // namespace sw
}  // namespace ama
