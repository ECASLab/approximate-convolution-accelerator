/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include <ap_fixed.h>

#include "convolution.hpp"

#define Q_BW 8
#define Q_K 3
#define Q_O 2

using DataType = ap_fixed<Q_BW, 1>;

static const int kOutputSize =
    ama::hw::convolvers::Winograd<DataType, Q_K, Q_O>::outputsize;
static const int kWindowSize =
    ama::hw::convolvers::Winograd<DataType, Q_K, Q_O>::windowsize;
static const int kKernelSize =
    ama::hw::convolvers::Winograd<DataType, Q_K, Q_O>::kernelsize;

void single_core_top_accel(DataType input[kWindowSize][kWindowSize],
                           DataType kernel[kKernelSize][kKernelSize],
                           DataType output[kOutputSize][kOutputSize]);
