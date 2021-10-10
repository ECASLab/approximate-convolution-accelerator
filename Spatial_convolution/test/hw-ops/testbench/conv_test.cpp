/*
 * Copyright 2021
 * Author: Alejandro Rodriguez Figueroa <alejandrorf@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <iostream>

#include "testbench.hpp"

#include "../../../includes/linear.hpp"
#include "../tops/spatialconv_top_accel.hpp"

/**
 * @brief Matrix use as test for the functions
 * It performs the convolution of two matrices.
 * @param a Matrix use as input
 * @param b Matrix empty matrix use for padding
 * @param c Matrix use as kernel
 * @param d print the convolute matrix
 */

int main(int argc, char **argv) {
  const float a[mRows][nCols] = {
      {2.3, 4.5, 1.8}, {3.3, 0.7, 0.0}, {5.0, 6.8, 9.9}};

  float b[mRows + (K - 1)][nCols + (K - 1)] = {0};

  const float c[K][K] = {{2.5, 2.5, 2.5}, {2.5, 2.5, 2.5}, {2.5, 2.5, 2.5}};

  float d[mRows + (K - 1)][nCols + (K - 1)] = {0};
  ama::sw::padding<float, mRows, nCols, K>(a, b);
  ama::sw::conv<float, mRows, nCols, K>(c, b, d);
  ama::utils::print_matrix<float, mRows, nCols, K>(d);
}
