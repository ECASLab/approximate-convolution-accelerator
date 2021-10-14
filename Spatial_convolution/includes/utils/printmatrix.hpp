/*
 * Copyright 2021
 * Author: Alejandro Rodriguez Figueroa <alejandrorf@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include <iostream>

namespace ama {
namespace utils {

template <typename T, int M, int N, int k>

/**
 * @brief Prints a matrix
 * @tparam T datatype
 * @tparam M the number of rows
 * @tparam N the number of columns
 * @tparam K the size of the kernel
 * @param res a matrix that will be printed in the cmd
 */

void print_matrix(const T res[M + (k - 1)][N + (k - 1)]) {
  int mk = M + (k - 1);
  int nk = N + (k - 1);
  for (int i = 0; i < mk; i++) {
    for (int j = 0; j < nk; j++) {
      std::cout << res[i][j] << ' ';
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
}  // namespace utils
}  // namespace ama
