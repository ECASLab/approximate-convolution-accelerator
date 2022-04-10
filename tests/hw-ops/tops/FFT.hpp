/*
 * Copyright 2022
 * Author: Alejandro Rodriguez Figueroa <alejandrorf@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include <ap_fixed.h>

#include "convolution.hpp"

#ifndef Q_BW
#define Q_BW 8
#endif

#ifndef Q_KS
#define Q_K 3
#else
#define Q_K Q_KS
#endif

#ifndef Q_O
#define Q_O 5
#endif

using DataType = ap_fixed<Q_BW, 1>;

static const int kOutputSize =
    ama::hw::convolvers::Spatial<DataType, Q_K, Q_O>::outputsize;
static const int kWindowSize =
    ama::hw::convolvers::Spatial<DataType, Q_K, Q_O>::windowsize;
static const int kKernelSize =
    ama::hw::convolvers::Spatial<DataType, Q_K, Q_O>::kernelsize;
static const int kRowsWindow = kWindowSize;


void FFT_top_accel(DataType input[kRowsWindow][kRowsWindow],
                        DataType kernel[kKernelSize][kKernelSize],
                        DataType output[kRowsWindow][kRowsWindow]);
