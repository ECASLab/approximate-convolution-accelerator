/*
 * Copyright 2021
 * Author: Alejandro Rodriguez Figueroa <alejandrorf@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include "../testbench/testbench.hpp"

/**
 * @brief Matrix spatial convolution and padding
 * It performs the convolution of two matrices and padding from header files.
 * @param selection the switch case int selection
 * @param a Matrix use as input or kernel depend of the function
 * @param b Matrix padd for a kernel size k and input already padd depend of the
 * function
 * @param c Matrix with the result of the convolution for specific function
 */
void spatialconv_top_accel(float a[mRows][nCols],
                           float b[mRows + (K - 1)][nCols + (K - 1)],
                           float c[mRows + (K - 1)][nCols + (K - 1)]);
