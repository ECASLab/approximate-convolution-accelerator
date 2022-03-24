/*
 * Copyright 2021
 * Author: Alejandro Rodriguez Figueroa <alejandrorf@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */
#pragma once
#include <complex>
#include <iostream>
#include <valarray>
#include "../utils/FFT_header.hpp"
#include "Convolver.hpp"

namespace ama {
namespace hw {
namespace convolvers {

using namespace ama::hw;

/**
 * fft convolution class
 * It specialises the convolver into the exact convolution class.
 * @tparam T datatype to work with.
 * @tparam K kernel side size
 * @tparam O output window size
 * @tparam ADD add functor
 * @tparam ADD mult functor
 * @tparam M is the high of the input image
 * @tparam N is the width of the input image
 */
template <typename T, int M, int N, int K, int O = 2,
          class ADD = arithmetic::exact::Add<T>,
          class MULT = arithmetic::exact::Mult<T>>
class fft : public Convolver<T, K, O, ADD, MULT> {
 public:
  /**
   * Execute the exact implementation
   * @param input input to convolve with the kernel
   * @param kernel kernel to convolve with
   * @param output output window
   */
  virtual void Execute(const T input[M][N], const T kernel[K][K],
                       T output[M][N]);

 private:
  /**
   * @brief Matrix fft convolution for array
   * It performs a lineal fft for array of complex numbers.
   * @param x input array
   * @param N size of the array
   */
  void fft_1D(CArray<T> &x);
  /**
   * @brief Matrix fft convolution for array
   * It performs a lineal fft for array of complex numbers.
   * @param input input matrix
   * @param N number of columns
   * @param M number of rows
   */
  void fft_2D(Complex<T> input[M][N]);

  /**
   * @brief Matrix inverse fft convolution for array
   * It performs a lineal fft for array of complex numbers.
   * @param x input array
   */
  void ifft(CArray<T> &x);

  /**
   * @brief Matrix fft convolution for array
   * It performs a lineal fft for array of complex numbers.
   * @param input input matrix
   * @param N number of columns
   * @param M number of rows
   */
  void ifft_2D(Complex<T> input[M][N]);

  /**
   * @brief Matrix padding
   * It performs the padding on a matrix for a kernel size k.
   * @param input_kernel Matrix original kernel
   * @param output_image kernel with the padding applied
   */
  void paddkernel_FFT(const T input_kernel[K][K],
                      Complex<T> output_image[M][N]);
  
  /**
   * @brief Matrix padding
   * It performs the padding on a matrix for a kernel size k.
   * @param input_kernel Matrix original kernel
   * @param output_image kernel with the padding applied
   */
  void Real_to_complex(const T input_image[M][N],
                      Complex<T> output_image[M][N]);
};

template <typename T, int M, int N, int K, int O, class ADD, class MULT>
inline void fft<T, M, N, K, O, ADD, MULT>::Execute(const T input[M][N],
                                                   const T kernel[K][K],
                                                   T output[M][N]) {
  Complex<T> a[M][N] = {0};
  Real_to_complex(input,a);


  fft_2D(a);

  Complex<T> b[M][N] = {0};

  paddkernel_FFT(kernel, b);

  fft_2D(b);

  const int i_mid = (M / 2) - 1;
  const int j_mid = (M / 2) - 1;

  // Hadamard product

  for (int i{0}; i < M; ++i) {
    for (int j{0}; j < N; ++j) {
      a[i][j] = a[i][j] * b[i][j];
    }
  }
  ifft_2D(a);

  // fixes the quadrants of output

  for (int i{0}; i < M; ++i) {
    for (int j{0}; j < N; ++j) {
      if (i <= i_mid && j <= j_mid) {
        output[i + i_mid][j + j_mid] = a[i][j].real();
      } else if (i < i_mid && j > j_mid) {
        output[i + i_mid][j - j_mid] = a[i][j].real();
      } else if (i >= i_mid && j <= j_mid) {
        output[i - i_mid][j + j_mid] = a[i][j].real();
      } else if (i > i_mid && j > j_mid) {
        output[i - i_mid][j - j_mid] = a[i][j].real();
      }
    }
  }
}

template <typename C, int M, int P, int K, int O, class ADD, class MULT>
inline void fft<C, M, P, K, O, ADD, MULT>::fft_1D(CArray<C> &x) {
  // DFT
  unsigned int N = x.size(), k = N, n;
  const C thetaT = kPI / N;
  Complex<C> phiT{cos(thetaT), -sin(thetaT)}, T;
  while (k > 1) {
    n = k;
    k >>= 1;
    phiT = phiT * phiT;
    T = 1.0L;
    for (unsigned int l = 0; l < k; l++) {
      for (unsigned int a = l; a < N; a += n) {
        unsigned int b = a + k;
        auto t = x[a] - x[b];
        x[a] += x[b];
        x[b] = t * T;
      }
      T *= phiT;
    }
  }
  // Decimate
  const auto m = static_cast<unsigned int>(log2(N));
  for (unsigned int a = 0; a < N; a++) {
    unsigned int b = a;
    // Reverse bits
    b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
    b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
    b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
    b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
    b = ((b >> 16) | (b << 16)) >> (32 - m);
    if (b > a) {
      auto t = x[a];
      x[a] = x[b];
      x[b] = t;
    }
  }
}

template <typename T, int M, int N, int K, int O, class ADD, class MULT>
inline void fft<T, M, N, K, O, ADD, MULT>::fft_2D(Complex<T> input[M][N]) {
  Complex<T> input_arr[M] = {0};
  // Row FFT
  for (int i{0}; i < M; ++i) {
    for (int j{0}; j < N; ++j) {
      input_arr[j] = input[i][j];
    }
    CArray<T> data(input_arr, N);
    fft_1D(data);
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
    fft_1D(data);
    for (int j{0}; j < M; ++j) {
      input[j][i] = data[j];
    }
  }
}

template <typename T, int M, int N, int K, int O, class ADD, class MULT>
inline void fft<T, M, N, K, O, ADD, MULT>::ifft(CArray<T> &x) {
  // conjugate the complex numbers
  x = x.apply(std::conj);

  // forward fft
  fft_1D(x);

  // conjugate the complex numbers again
  x = x.apply(std::conj);

  // scale the numbers
  x /= x.size();
}

template <typename T, int M, int N, int K, int O, class ADD, class MULT>
inline void fft<T, M, N, K, O, ADD, MULT>::ifft_2D(Complex<T> input[M][N]) {
  Complex<T> input_arr[M] = {0};

  // Columns iFFT
  for (int i{0}; i < N; ++i) {
    for (int j{0}; j < M; ++j) {
      input_arr[j] = input[j][i];
    }
    CArray<T> data(input_arr, M);
    ifft(data);
    for (int j{0}; j < M; ++j) {
      input[j][i] = data[j];
    }
  }

  // Row iFFT
  for (int i{0}; i < M; ++i) {
    for (int j{0}; j < N; ++j) {
      input_arr[j] = input[i][j];
    }
    CArray<T> data(input_arr, N);
    ifft(data);
    for (int j{0}; j < N; ++j) {
      input[i][j] = data[j];
    }
  }
}

template <typename T, int M, int N, int K, int O, class ADD, class MULT>
inline void fft<T, M, N, K, O, ADD, MULT>::paddkernel_FFT(
    const T input_kernel[K][K], Complex<T> output_image[M][N]) {
  int start[2] = {0};
  const int offset = (K + 1) / 2;

  start[0] = (M / 2) - offset;
  start[1] = (N / 2) - offset;

  for (int i{0}; i < K; ++i) {
    for (int j{0}; j < K; ++j) {
      output_image[start[0] + i][start[1] + j] = input_kernel[i][j];
    }
  }
}

template <typename T, int M, int N, int K, int O, class ADD, class MULT>
inline void fft<T, M, N, K, O, ADD, MULT>::Real_to_complex(
    const T input_image[M][N],Complex<T> output_image[M][N]) {
  for (int i{0}; i < M; ++i) {
    for (int j{0}; j < N; ++j) {
      output_image[i][j] = input_image[i][j];
    }
  }
}
} /* namespace convolvers */
} /* namespace hw */
} /* namespace ama */
