/*
 * Copyright 2022
 * Author: Alejandro Rodriguez Figueroa <alejandrorf@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include "FFT.hpp"

#include "hw-ops/FFT_class.hpp"

void FFT_top_accel(DataType input[kRowsWindow][kRowsWindow],
                   DataType kernel[kKernelSize][kKernelSize],
                   DataType output[kRowsWindow][kRowsWindow]) {
  ama::hw::convolvers::fft<DataType, Q_K, Q_O> op;
  op.Execute(input, kernel, output);
}
