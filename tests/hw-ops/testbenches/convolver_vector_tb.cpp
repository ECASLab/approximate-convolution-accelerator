/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <iostream>

#include "convolver_vector.hpp"
#include "utils/printmatrix.hpp"

static DataType kKernel[Q_K][Q_K] = {
    {0.0625, 0.125, 0.0625}, {0.125, 0.25, 0.125}, {0.0625, 0.125, 0.0625}};

static DataType kOnes[7][4] = {{0.5, 0.5, 0.5, 0.5}, {0.5, 0.1, 0.1, 0.5},
                               {0.5, 0.1, 0.1, 0.5}, {0.5, 0.1, 0.1, 0.5},
                               {0.5, 0.1, 0.1, 0.5}, {0.5, 0.1, 0.1, 0.5},
                               {0.5, 0.5, 0.5, 0.5}};

int main(int, char**) {
  int ret = 0;
  DataType output[4][2];

  /* Print input matrices */
  std::cout << "Input matrix: " << std::endl;
  ama::utils::print_matrix<DataType, 7, 4>(kOnes);
  std::cout << "Kernel matrix: " << std::endl;
  ama::utils::print_matrix<DataType, Q_K>(kKernel);

  convolver_vector_top_accel(kOnes, kKernel, output);

  /* Print output matrices */
  std::cout << "Output matrix: " << std::endl;
  ama::utils::print_matrix<DataType, 4, 2>(output);

  return ret;
}
