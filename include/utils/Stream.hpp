/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include <ap_int.h>

template <class T>
struct StreamPayloadT {
  T data;
  ap_uint<1> last;
  ap_uint<T::width / 8> keep;
};

template <class P>
using StreamPortT = hls::stream<P>;
