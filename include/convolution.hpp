/*
 * Copyright 2021
 * Author: Alejandro Rodriguez Figueroa <alejandrorf@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

/* Hardware ops */
#ifndef SW_ONLY
#include "hw-ops/Convolution.hpp"
#include "hw-ops/Padding.hpp"
#include "hw-ops/FFT.hpp"
#endif

/* Software ops */
#include "sw-ops/Convolution.hpp"
#include "sw-ops/Padding.hpp"
#include "sw-ops/FFT.hpp"
#include "sw-ops/FFT_2D.hpp"
#include "sw-ops/IFFT.hpp"
#include "sw-ops/IFFT_2D.hpp"

/* Utils */
#include "utils/printmatrix.hpp"
#include "utils/Kernel3.hpp"
#include "utils/Kernel5.hpp"
#include "utils/Kernel7.hpp"
