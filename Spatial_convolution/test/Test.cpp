/*
 * Copyright 2021
 * Author: Alejandro Rodriguez Figueroa <alejandrorf@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <iostream>

#include "../includes/sw-ops/Convolution.hpp"
#include "../includes/sw-ops/Padding.hpp"

#define K 3
#define mRows 3
#define nCols 3

/**
 * @brief Matrix spatial convolution and padding
 * It performs the convolution of two matrices and padding from header files.
 * @param selection the switch case int selection
 * @param a Matrix use as input or kernel depend of the function
 * @param b Matrix padd for a kernel size k and input already padd depend of the function
 * @param c Matrix with the result of the convolution for specific function
 */

void operations_top_sw(int selection, const float a[mRows][nCols],
                       float b[mRows + (K-1)][nCols + (K-1)], float c[mRows + (K-1)][nCols + (K-1)]) {
  switch (selection) {
    case 0:
      ama::sw::padding<float, mRows, nCols, K>(a, b);
      break;
    case 1:
      ama::sw::conv<float, mRows, nCols, K>(a, b, c);
      break;
  }
}

/**
 * @brief Prints a matrix
 * @param res a matrix that will be printed in the cmd
 */
 
void print_matrix(const float res[mRows + (K-1)][nCols + (K-1)]) {
  int m = mRows + (K-1);
  int n = nCols + (K-1);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << res[i][j] << ' ';
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

/**
 * @brief Matrix use as test for the functions
 * It performs the convolution of two matrices.
 * @param a Matrix use as input
 * @param b Matrix empty matrix use for padding
 * @param c Matrix use as kernel
 * @param d print the convolute matrix
 */

int main() {
  const float a[mRows][nCols] = {{2.3, 4.5, 1.8}, {3.3, 0.7, 0.0}, {5.0, 6.8, 9.9}};

  float b[mRows + (K-1)][nCols + (K-1)] = {0};

  const float c[K][K] = {{2.5, 2.5, 2.5}, {2.5, 2.5, 2.5}, {2.5, 2.5, 2.5}};

  float d[mRows + (K-1)][nCols + (K-1)] = {0};
  operations_top_sw(0, a, b, d);
  operations_top_sw(1, c, b, d);
  print_matrix(d);
  return 0;
}
