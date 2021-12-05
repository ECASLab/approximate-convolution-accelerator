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

/* Utils */
#include "utils/printmatrix.hpp"
