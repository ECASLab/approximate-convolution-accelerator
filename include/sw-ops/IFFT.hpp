/*
 * Copyright 2021
 * Author: Alejandro Rodriguez Figueroa <alejandrorf@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <complex>
#include <iostream>
#include <valarray>
#include "FFT.hpp"
#include "../utils/FFT_header.hpp"

#pragma once

namespace ama {
namespace sw {

/**
 * @brief Matrix inverse fft convolution for array
 * It performs a lineal fft for array of complex numbers.
 * @param x input array
 */

template <typename T>

void ifft(CArray<T> &x) {
  // conjugate the complex numbers
  x = x.apply(std::conj);

  // forward fft
  ama::sw::fft<T>(x);

  // conjugate the complex numbers again
  //x = x.apply(std::conj);
  T scale = 1. / x.size();
  x *= scale;

  // scale the numbers
  x /= x.size();
}
}  // namespace sw
}  // namespace ama
