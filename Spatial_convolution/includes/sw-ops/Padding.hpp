/*
 * Copyright 2021
 * Author: Alejandro Rodriguez Figueroa <alejandrorf@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */
#include <iostream>
#pragma once

namespace ama {
namespace sw {

template <typename T, int M, int N, int k>
/**
 * @brief Matrix padding
 * It performs the padding on a matrix for a kernel size k.
 * @param imageori Matrix original matrix
 * @param imagepadd Matrix with the padding applied
 */
void padding(const T imageori[M][N], T imagepadd[M + (k - 1)][N + (k - 1)]) {
  int start = k / 2;
  //	std::cout<< start<< std::endl;
  for (int i = 0; i < M + k - 1; i++) {
    for (int j = 0; j < N + k - 1; j++) {
      if (i < start || i > M || j < start || j > N) {
        //      		std::cout<< "si agrego" << " ";
        //      		std::cout<< 0 << std::endl;
        imagepadd[i][j] = 0;
      } else {
        imagepadd[i][j] = imageori[i - start][j - start];
        // std::cout<< "si agrego" << " " << i << " " << j << std::endl;
        // std::cout<< imagepadd[i][j] << std::endl;
      }
    }
  }
}
};  // namespace sw
};  // namespace ama
