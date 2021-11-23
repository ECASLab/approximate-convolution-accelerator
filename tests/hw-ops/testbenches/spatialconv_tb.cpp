/*
 * Copyright 2021
 * Author: Alejandro Rodriguez Figueroa <alejandrorf@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <iostream>

#include "testbench.hpp"

/* Files from include */
#include "convolution.hpp"

/* Files from tops */
#include "spatialconv.hpp"

/**
 * @brief Matrix use as test for the functions
 * It performs the convolution of an image against a general kernel.
 * @param a Matrix use as input
 * @param b Matrix empty matrix use for padding
 * @param c Matrix use as kernel
 * @param d print the convolute matrix
 */

int main() {
  float a[mRows][nCols] = {
      {2.3, 4.5, 1.8}, {3.3, 0.7, 0.0}, {5.0, 6.8, 9.9}};

  float b[mRows + (K - 1)][nCols + (K - 1)] = {0};
  #if K == 5 
  float c[5][5] = {{0.003663003, 0.01465201465, 0.02564102564, 0.01465201465, 0.003663003}, 
                     {0.01465201465, 0.05860805861, 0.09523809524, 0.05860805861, 0.01465201465}, 
                     {0.02564102564, 0.09523809524, 0.1501831502, 0.09523809524, 0.02564102564}, 
                     {0.01465201465, 0.05860805861, 0.09523809524, 0.05860805861, 0.01465201465}, 
                     {0.003663003, 0.01465201465, 0.02564102564, 0.01465201465, 0.003663003}};
  #elif K == 7
  float c[7][7] = {{0, 0, 0.000997008, 0.001994017, 0.000997008, 0, 0}, 
                     {0, 0.002991026, 0.01296111665, 0.02193419741, 0.01296111665, 0.002991026, 0}, 
                     {0.000997008, 0.01296111665, 0.05882352941, 0.09670987039, 0.05882352941, 0.01296111665, 0.000997008}, 
                     {0.001994017, 0.02193419741, 0.09670987039, 0.1585244267, 0.09670987039, 0.02193419741, 0.001994017},
                     {0.000997008, 0.01296111665, 0.05882352941, 0.09670987039, 0.05882352941, 0.01296111665, 0.000997008},
                     {0, 0.002991026, 0.01296111665, 0.02193419741, 0.01296111665, 0.002991026, 0}, 
                     {0, 0, 0.000997008, 0.001994017, 0.000997008, 0, 0}};
  #else
  float c[3][3] = {{0.0625, 0.125, 0.0625}, 
                     {0.125, 0.25, 0.125}, 
                     {0.0625, 0.125, 0.0625}};
  #endif
  float d[mRows + (K - 1)][nCols + (K - 1)] = {0};
  ama::hw::padding<float, mRows, nCols, K>(a, b);
  spatialconv_top_accel(c, b, d);
  ama::utils::print_matrix<float, mRows + (K - 1), nCols + (K - 1)>(d);
}
