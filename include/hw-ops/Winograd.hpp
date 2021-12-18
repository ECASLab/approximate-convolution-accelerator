/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

/*
 * Git:
 * https://github.com/lirui-shanghaitech/A-convolution-kernel-implemented-by-Vivado-HLS
 * Paper: https://ceca.pku.edu.cn/media/lw/6940b5b0e09259131ff19334f3efeecd.pdf
 *
 * https://github.com/xliu0709/WinoCNN
 */

#pragma once

namespace ama {
namespace hw {
namespace winograd {
namespace core {

template <typename T, int K> class Exact {
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
  void Execute(const T window[windowsize][windowsize],
               const T kernel[kernelsize][kernelsize],
               T output[outputsize][outputsize]) {
    T w_window[windowsize][windowsize];
    T w_kernel[windowsize][windowsize];
    T w_output[windowsize][windowsize];

    /* Transform */
    TransformInput(window, w_window);
    TransformKernel(kernel, w_kernel);

    /* Convolve */
    Hadamard(w_kernel, w_window, w_output);

    /* Transform back */
    DetransformOutput(w_output, output);
  }

private:
  /**
   * Performs the transformation of the Input into the Winograd Domain
   * The operation performed is BtZB
   * @param w input in space domain
   * @param w_k transformed input into Winograd domain
   */
  void TransformInput(const T w[windowsize][windowsize],
                      T w_w[windowsize][windowsize]);

  /**
   * Performs the transformation of the kernel into the Winograd Domain
   * The operation performed is GfGt
   * @param k kernel in space domain
   * @param w_k transformed kernel into Winograd domain
   */
  void TransformKernel(const T k[kernelsize][kernelsize],
                       T w_k[windowsize][windowsize]);

  /**
   * Performs the Hadamard product between two spectrums
   * @param w_k kernel in Winograd domain
   * @param w_w input in Winograd domain
   * @param w_kw output in Winograd domain
   */
  void Hadamard(const T w_k[windowsize][windowsize],
                const T w_w[windowsize][windowsize],
                T w_kw[windowsize][windowsize]);

  /**
   * Performs the transformation of the output into the space Domain
   * The operation performed is AtHA
   * @param w_h output in Winograd domain
   * @param h transformed output into space domain
   */
  void DetransformOutput(const T w_h[windowsize][windowsize],
                         T h[outputsize][outputsize]);
};

template <typename T, int K>
inline void Exact<T, K>::DetransformOutput(
    const T w_h[Exact<T, K>::windowsize][Exact<T, K>::windowsize],
    T h[Exact<T, K>::outputsize][Exact<T, K>::outputsize]) {
  h[0][0] = w_h[0][0] + w_h[0][1] + w_h[0][2] + w_h[1][0] + w_h[1][1] +
            w_h[1][2] + w_h[2][0] + w_h[2][1] + w_h[2][2];
  h[0][1] = w_h[0][1] - w_h[0][2] - w_h[0][3] + w_h[1][1] - w_h[1][2] -
            w_h[1][3] + w_h[2][1] - w_h[2][2] - w_h[2][3];
  h[1][0] = w_h[1][0] + w_h[1][1] + w_h[1][2] - w_h[2][0] - w_h[2][1] -
            w_h[2][2] - w_h[3][0] - w_h[3][1] - w_h[3][2];
  h[1][1] = w_h[1][1] - w_h[1][2] - w_h[1][3] - w_h[2][1] + w_h[2][2] +
            w_h[2][3] - w_h[3][1] + w_h[3][2] + w_h[3][3];
}

template <typename T, int K>
inline void Exact<T, K>::Hadamard(
    const T w_k[Exact<T, K>::windowsize][Exact<T, K>::windowsize],
    const T w_w[Exact<T, K>::windowsize][Exact<T, K>::windowsize],
    T w_kw[Exact<T, K>::windowsize][Exact<T, K>::windowsize]) {
winograd_exact_hadamard_i:
  for (int i{0}; i < windowsize; ++i) {
#pragma HLS UNROLL
  winograd_exact_hadamard_j:
    for (int j{0}; j < windowsize; ++j) {
#pragma HLS UNROLL
      w_kw[i][j] = w_k[i][j] * w_w[i][j];
    }
  }
}

template <typename T, int K>
inline void Exact<T, K>::TransformInput(
    const T w[Exact<T, K>::windowsize][Exact<T, K>::windowsize],
    T w_w[Exact<T, K>::windowsize][Exact<T, K>::windowsize]) {
  /* TODO: Factorise operations */
  w_w[0][0] = w[0][0] - w[0][2] - w[2][0] + w[2][2];
  w_w[0][1] = w[0][1] + w[0][2] - w[2][1] - w[2][2];
  w_w[0][2] = -w[0][1] + w[0][2] + w[2][1] - w[2][2];
  w_w[0][3] = w[0][1] - w[0][3] - w[2][1] + w[2][3];
  w_w[1][0] = w[1][0] - w[1][2] + w[2][0] - w[2][2];
  w_w[1][1] = w[1][1] + w[1][2] + w[2][1] + w[2][2];
  w_w[1][2] = -w[1][1] + w[1][2] - w[2][1] + w[2][2];
  w_w[1][3] = w[1][1] - w[1][3] + w[2][1] - w[2][3];
  w_w[2][0] = -w[1][0] + w[1][2] + w[2][0] - w[2][2];
  w_w[2][1] = -w[1][1] - w[1][2] + w[2][1] + w[2][2];
  w_w[2][2] = w[1][1] - w[1][2] - w[2][1] + w[2][2];
  w_w[2][3] = -w[1][1] + w[1][3] + w[2][1] - w[2][3];
  w_w[3][0] = w[1][0] - w[1][2] - w[3][0] + w[3][2];
  w_w[3][1] = w[1][1] + w[1][2] - w[3][1] - w[3][2];
  w_w[3][2] = -w[1][1] + w[1][2] + w[3][1] - w[3][2];
  w_w[3][3] = w[1][1] - w[1][3] - w[3][1] + w[3][3];
}

template <typename T, int K>
inline void Exact<T, K>::TransformKernel(
    const T k[Exact<T, K>::kernelsize][Exact<T, K>::kernelsize],
    T w_k[Exact<T, K>::windowsize][Exact<T, K>::windowsize]) {
  /* TODO: Factorise operations */
  w_k[0][0] = k[0][0];
  w_k[0][1] = (k[0][0] + k[0][1] + k[0][2]) >> 1;
  w_k[0][2] = (k[0][0] - k[0][1] + k[0][2]) >> 1;
  w_k[0][3] = k[0][2];
  w_k[1][0] = (k[0][0] + k[1][0] + k[2][0]) >> 1;
  w_k[1][1] = (k[0][0] + k[0][1] + k[0][2] + k[1][0] + k[1][1] + k[1][2] +
               k[2][0] + k[2][1] + k[2][2]) >>
              2;
  w_k[1][2] = (k[0][0] - k[0][1] + k[0][2] + k[1][0] - k[1][1] + k[1][2] +
               k[2][0] - k[2][1] + k[2][2]) >>
              2;
  w_k[1][3] = (k[0][2] + k[1][2] + k[2][2]) >> 1;
  w_k[2][0] = (k[0][0] - k[1][0] + k[2][0]) >> 1;
  w_k[2][1] = (k[0][0] + k[0][1] + k[0][2] - k[1][0] - k[1][1] - k[1][2] +
               k[2][0] + k[2][1] + k[2][2]) >>
              2;
  w_k[2][2] = (k[0][0] - k[0][1] + k[0][2] - k[1][0] + k[1][1] - k[1][2] +
               k[2][0] - k[2][1] + k[2][2]) >>
              2;
  w_k[2][3] = (k[0][2] - k[1][2] + k[2][2]) >> 1;
  w_k[3][0] = k[2][0];
  w_k[3][1] = (k[2][0] + k[2][1] + k[2][2]) >> 1;
  w_k[3][2] = (k[2][0] - k[2][1] + k[2][2]) >> 1;
  w_k[3][3] = k[2][2];
}

} /* namespace core */
} /* namespace winograd */
} /* namespace hw */
} /* namespace ama */
