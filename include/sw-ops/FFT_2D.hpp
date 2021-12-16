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

namespace ama {
namespace sw {

template <typename Complex, typename CArray, int M, int N>

// typedef std::complex<float> Complex;
// typedef std::valarray<Complex> CArray;


void fft_2D(Complex input[M][N]) {
    Complex input_arr[M] = {0};
    //Row FFT
    for (int i{0}; i < M; ++i) {
       for (int j{0}; j < N; ++j) {
       input_arr[j] = input[i][j];
     }
     CArray data(input_arr, N);
     ama::sw::fft(data);
      for (int j{0}; j < N; ++j) {
       input[i][j] = data[j];
     }
   }
    //Columns FFT
    for (int i{0}; i < N; ++i) {
       for (int j{0}; j < M; ++j) {
       input_arr[j] = input[j][i];
     }
     CArray data(input_arr, M);
     ama::sw::fft(data);
      for (int j{0}; j < M; ++j) {
       input[j][i] = data[j];
     }
   }

}
}  // namespace sw
}  // namespace ama