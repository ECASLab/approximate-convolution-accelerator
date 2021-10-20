/*
 * Copyright 2021
 * Author: Alejandro Rodriguez Figueroa <alejandrorf@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include "spatialconv.hpp"

#include "convolution.hpp"

void spatialconv_top_accel(float a[K][K],
                           float b[mRows + (K - 1)][nCols + (K - 1)],
                           float c[mRows + (K - 1)][nCols + (K - 1)]) {
  ama::hw::conv<float, mRows, nCols, K>(a, b, c);
}
