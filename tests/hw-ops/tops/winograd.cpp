/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include "winograd.hpp"

#include "hw-ops/Winograd.hpp"

void winograd_top_accel(DataType input[Q_K + 1][Q_K + 1],
                        DataType kernel[Q_K][Q_K],
                        DataType output[Q_K - 1][Q_K - 1]) {
#pragma HLS ARRAY_PARTITION variable=input complete dim=0
#pragma HLS ARRAY_PARTITION variable=kernel complete dim=0
#pragma HLS ARRAY_PARTITION variable=output complete dim=0
  ama::hw::winograd::core::Exact<DataType, Q_K> op;
  op.Execute(input, kernel, output);
}
