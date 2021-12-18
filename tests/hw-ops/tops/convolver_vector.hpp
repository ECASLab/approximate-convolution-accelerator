/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include <ap_fixed.h>

#define Q_BW 8
#define Q_K 3
using DataType = ap_fixed<Q_BW, 1>;

void convolver_vector_top_accel(DataType input[7][4], DataType kernel[Q_K][Q_K],
                                DataType output[4][2]);
