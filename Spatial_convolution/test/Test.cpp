/*
 * Copyright 2021
 * Author: Alejandro Rodriguez Figueroa <alejandrorf@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <iostream>

#include "../includes/sw-ops/Convolution.hpp"
#include "../includes/sw-ops/Padding.hpp"

#define kCols 3
#define kRows 3

void operations_top_sw(int selection, const float a[kCols][kRows],
                       float b[5][5], float c[5][5]) {
  switch (selection) {
    case 0:
      ama::sw::padding<float, 3, 3, 3>(a, b);
      break;
    case 1:
      ama::sw::conv<float, 3, 3, 3>(a, b, c);
      break;
  }
}

/**
 * @brief Prints a matrix
 * @param d print the convolute matrix
 */
void print_matrix(const float res[5][5]) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      std::cout << res[i][j] << ' ';
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

int main() {
  std::cout << kCols << std::endl << kRows << std::endl;
  int k = 3;
  const float a[3][3] = {{2.3, 4.5, 1.8}, {3.3, 0.7, 0.0}, {5.0, 6.8, 9.9}};

  float b[5][5] = {0};

  const float c[3][3] = {{2.5, 2.5, 2.5}, {2.5, 2.5, 2.5}, {2.5, 2.5, 2.5}};

  float d[5][5] = {0};
  operations_top_sw(0, a, b, d);
  // print_matrix(b);
  operations_top_sw(1, c, b, d);
  print_matrix(d);
  return 0;
}
