/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include "winograd.hpp"

void winograd_top_accel(DataType input[kRowsWindow][kWindowSize],
                        DataType kernel[kKernelSize][kKernelSize],
                        DataType output[kRowsOutput][kOutputSize]) {
#if Q_K == 3
  ama::hw::convolvers::Winograd<DataType, Q_K, Q_O> op;
#elif Q_K == 5
  ama::hw::convolvers::Winograd5<DataType, Q_K, Q_O> op;
#elif Q_K == 7
  ama::hw::convolvers::Winograd7<DataType, Q_K, Q_O> op;
#else
  #error Cannot find the proper accel
#endif
  op.Execute(input, kernel, output);
}
