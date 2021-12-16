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

template<typename T>
using Complex = std::complex<T>;

template<typename T>
using CArray = std::valarray<Complex<T>>;

template<typename T>

void ifft(CArray<T> &x) {
    // conjugate the complex numbers
    x = x.apply(std::conj);
 
    // forward fft
    ama::sw::fft<T>( x );
 
    // conjugate the complex numbers again
    x = x.apply(std::conj);
 
    // scale the numbers
    x /= x.size();
}
}  // namespace sw
}  // namespace ama