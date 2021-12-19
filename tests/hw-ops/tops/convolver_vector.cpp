/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include "convolver_vector.hpp"

#include "hw-ops/Space.hpp"

// This is the template loop. This is written in such way that it executes from
// the greater index to 0
template <int N, class Wrapper>
struct Looper {
  static void impl(DataType input[7][4], DataType kernel[Q_K][Q_K],
                   DataType output[4][2]) {
    Wrapper op{};
    op.Execute(&input[3 * (N - 1)], kernel, &output[2 * (N - 1)]);

    // Continue Loop - The next i = i - 1
    Looper<(N - 1), Wrapper>::impl(input, kernel, output);
  }
};

// This specialisation is the last index action and stop condition
template <class Wrapper>
struct Looper<0, Wrapper> {
  static void impl(DataType input[7][4], DataType kernel[Q_K][Q_K],
                   DataType output[4][2]) {
    // Do Nothing (terminate loop)
  }
};

// This is the loop caller. It is needed to generate the 'Args' for template
// deduction
template <int N, class Wrapper>
void do_unroll(DataType input[7][4], DataType kernel[Q_K][Q_K],
               DataType output[4][2]) {
  Looper<N, Wrapper>::impl(input, kernel, output);
}

/* Execute all the machinary */
template <int B>
void do_all(DataType input[7][4], DataType kernel[Q_K][Q_K],
            DataType output[4][2]) {
  do_unroll<B, ama::hw::space::core::Exact<DataType, Q_K>>(input, kernel,
                                                           output);
}

/* The convolution happens in row-major but it is transferred by columns */
void convolver_vector_top_accel(DataType input[7][4], DataType kernel[Q_K][Q_K],
                                DataType output[4][2]) {
  do_all<2>(input, kernel, output);
}
