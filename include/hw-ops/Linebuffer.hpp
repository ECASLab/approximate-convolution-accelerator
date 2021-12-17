/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include "utils/Stream.hpp"

namespace ama {
namespace hw {

template <typename T, class EXE, int W = 640, int WIN = 4>
class LineBuffer {
 public:
  /* Constants */
  static const int kWidth = W;
  static const int kWinSize = WIN;

  /* Types */
  typename StreamPayload = StreamPayloadT<T>;
  typename StreamPort = StreamPortT<StreamPayload>;

  void Execute(StreamPort& output, StreamPort& input, const int width,
               const int height, const T ** kernel);

 private:
  /* Engine is the linebuffer executor */
  static const EXE engine_{};

  /* Internal executor */
  void ExecuteConvolution(StreamPort& output, StreamPort& input, const int width,
               const int height, const T ** kernel, T ** line_buffer, T ** window1);
};

template <typename T, class EXE, int W, int WIN>
void LineBuffer<T, EXE, W, WIN>::ExecuteConvolution(
    LineBuffer<T, EXE, W, WIN>::StreamPort& output,
    LineBuffer<T, EXE, W, WIN>::StreamPort& input, const int width,
    const int height, const T ** kernel, T ** line_buffer, T ** window1) {
  T window2[WIN][WIN];
  T outwin[WIN - 2][WIN - 2];

#pragma HLS ARRAY_PARTITION variable = window complete dim = 0
  for (int yidx{0}; yidx < height; ++yidx) {
    for (int xidx{0}; xidx < width; ++xidx) {
#pragma HLS PIPELINE
      /* Compute current window */
      this->engine_(window, kernel, output);

      /* TODO: Create a method for filling the next window, swap pointers and load the output window. Another line buffer may be needed */
  }
}

template <typename T, class EXE, int W, int WIN>
void LineBuffer<T, EXE, W, WIN>::Execute(
    LineBuffer<T, EXE, W, WIN>::StreamPort& output,
    LineBuffer<T, EXE, W, WIN>::StreamPort& input, const int width,
    const int height, const T ** kernel) {
  const int kLineBufferHeight = WIN - 1;
  /* Buffers required for the line buffer convolution */
  T line_buffer[kLineBufferHeight][W];
  T window[WIN][WIN];
#pragma HLS ARRAY_PARTITION variable = line_buffer complete dim = 0
#pragma HLS ARRAY_PARTITION variable = window complete dim = 0
  memset(window[0], 0, WIN * WIN);

  /*
   * Fill the line buffer
   *
   * LLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
   * LLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
   * LLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
   * xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
   */
  for (int j{0}; j < kLineBufferHeight; ++j) {
    for (int i{0}; i < width; ++i) {
      line_buffer[j][i] = input.read().data;
    }
  }

  /*
   * Complete de initial window
   * PPPP
   * PWWWLLLLLLLLLLLLLLLLLLLLLLLLLLL
   * PWWWLLLLLLLLLLLLLLLLLLLLLLLLLLL
   * PWWWLLLLLLLLLLLLLLLLLLLLLLLLLLL
   *  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
   * FIXME: According to dynamic kernel size
   */
  for (int j{1}; j < WIN; ++j) {
    for (int i{1}; i < WIN; ++i) {
      window[j][i] = line_buffer[j - 1][i - 1];
    }
  }

  /*
   * It should be ready to start computing
   */
  ExecuteConvolution(output, input, width, height, kernel, line_buffer, window);
}

}  // namespace hw
}  // namespace ama
