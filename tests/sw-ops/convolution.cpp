/*
 * Copyright 2021
 * Author: Alejandro Rodriguez Figueroa <alejandrorf@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <iostream>

#include "convolution.hpp"

#define K 7
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
                       float b[mRows + (K-1)][nCols + (K-1)], float c[mRows + (K-1)][nCols + (K-1)], float d[K][K]) {
  switch (selection) {
    case 0:
      ama::sw::padding<float, mRows, nCols, K>(a, b);
      break;
    case 1:
      ama::sw::conv<float, mRows, nCols, K>(d, b, c);
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

  float b5[mRows + (4)][nCols + (4)] = {0};
  float b7[mRows + (6)][nCols + (6)] = {0};
  float b3[mRows + (2)][nCols + (2)] = {0};
  float c5[5][5] = {{0.003663003, 0.01465201465, 0.02564102564, 0.01465201465, 0.003663003}, 
                     {0.01465201465, 0.05860805861, 0.09523809524, 0.05860805861, 0.01465201465}, 
                     {0.02564102564, 0.09523809524, 0.1501831502, 0.09523809524, 0.02564102564}, 
                     {0.01465201465, 0.05860805861, 0.09523809524, 0.05860805861, 0.01465201465}, 
                     {0.003663003, 0.01465201465, 0.02564102564, 0.01465201465, 0.003663003}};
  float c7[7][7] = {{0, 0, 0.000997008, 0.001994017, 0.000997008, 0, 0}, 
                     {0, 0.002991026, 0.01296111665, 0.02193419741, 0.01296111665, 0.002991026, 0}, 
                     {0.000997008, 0.01296111665, 0.05882352941, 0.09670987039, 0.05882352941, 0.01296111665, 0.000997008}, 
                     {0.001994017, 0.02193419741, 0.09670987039, 0.1585244267, 0.09670987039, 0.02193419741, 0.001994017},
                     {0.000997008, 0.01296111665, 0.05882352941, 0.09670987039, 0.05882352941, 0.01296111665, 0.000997008},
                     {0, 0.002991026, 0.01296111665, 0.02193419741, 0.01296111665, 0.002991026, 0}, 
                     {0, 0, 0.000997008, 0.001994017, 0.000997008, 0, 0}};
  float c3[3][3] = {{0.0625, 0.125, 0.0625}, 
                     {0.125, 0.25, 0.125}, 
                     {0.0625, 0.125, 0.0625}};
  float d5[mRows + (4)][nCols + (4)] = {0};
  float d7[mRows + (6)][nCols + (6)] = {0};
  float d3[mRows + (2)][nCols + (2)] = {0};
  //if (K == 5) {
    //operations_top_sw(0, a, b5, d5, c5);
    //operations_top_sw(1, a, b5, d5, c5);
    //print_matrix(d5);
  //} else if (K == 7){
    operations_top_sw(0, a, b7, d7, c7);
    print_matrix(b7);
    operations_top_sw(1, a, b7, d7, c7);
    print_matrix(d7);
  //} else {
    //operations_top_sw(0, a, b3, d3, c3);
    //operations_top_sw(1, a, b3, d3, c3);
    //print_matrix(d3);
  //}
  return 0;
}
