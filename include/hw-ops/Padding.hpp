/*
 * Copyright 2021
 * Author: Alejandro Rodriguez Figueroa <alejandrorf@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

namespace ama {
namespace hw {

template <typename T, int M, int N, int k>

/**
 * @brief Matrix padding
 * It performs the padding on a matrix for a kernel size k.
 * @tparam T datatype
 * @tparam M the number of rows
 * @tparam N the number of columns
 * @tparam K the size of the kernel
 * @param input_image Matrix original matrix
 * @param output_image Matrix with the padding applied
 */

void padding(const T input_image[M][N],
             T output_image[M + (k - 1)][N + (k - 1)]) {
  const int start = k / 2;
  for (int i{0}; i < M + k - 1; ++i) {
      for (int j{0}; j < N + k - 1; ++j) {
          bool padding = i < start || i > M || j < start || j > N;
          output_image[i][j] = padding ? 0 : input_image[i - start][j - start];
        }
    }
}
}  // namespace hw
}  // namespace ama
