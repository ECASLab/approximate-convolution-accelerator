/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include "convolver_vector.hpp"

#include "hw-ops/Space.hpp"

/*
 * FIXME: Review the kernel generalisation. For now, a Q_K = 3 is assumed
 */

/*
 N -> number of accelerators
 input[N * 2 + 2][4]
 output[N * 2][2]
 N = Convolve<Datatype, Q_K>::outputsize
 */

/*
 * This is the template loop. This is written in such way that it executes from
 * the greater index to 0
 */
template <int N, int NT, class Wrapper>
struct Looper {
  static void impl(
      DataType input[NT * Wrapper::outputsize + 2][Wrapper::windowsize],
      DataType kernel[Wrapper::kernelsize][Wrapper::kernelsize],
      DataType output[NT * Wrapper::outputsize][Wrapper::outputsize]) {
#pragma HLS INLINE /* Important! Inlining the execution allows parallelism */
    /* Execute PE */
    Wrapper op{};
    op.Execute(&input[2 * (N - 1)], kernel, &output[2 * (N - 1)]);

    /* Continue Loop - The next i = i - 1 */
    Looper<(N - 1), NT, Wrapper>::impl(input, kernel, output);
  }
};

/* This specialisation is the last index action and stop condition */
template <int NT, class Wrapper>
struct Looper<0, NT, Wrapper> {
  static void impl(
      DataType input[NT * Wrapper::outputsize + 2][Wrapper::windowsize],
      DataType kernel[Wrapper::kernelsize][Wrapper::kernelsize],
      DataType output[NT * Wrapper::outputsize][Wrapper::outputsize]) {
#pragma HLS INLINE /* Important! Inlining the execution allows parallelism */
    /* Do Nothing (terminate loop) */
  }
};

/*
 * This is the loop caller. It is needed to generate the 'Args' for template
 * deduction
 */
template <int N, class Wrapper, typename... Args>
void do_unroll(Args... args) {
#pragma HLS INLINE /* Important! Inlining the execution allows parallelism */
  Looper<N, N, Wrapper>::impl(args...);
}

/* Execute all the machinary: let's suppose that this wraps all the PEs  */
template <int B, typename... Args>
void do_all(Args... args) {
  do_unroll<B, ama::hw::space::core::Exact<DataType, Q_K>>(args...);
}

/* The convolution happens in row-major but it is transferred by columns */
void convolver_vector_top_accel(DataType input[Q_ACCEL * 2 + 2][4],
                                DataType kernel[Q_K][Q_K],
                                DataType output[Q_ACCEL * 2][2]) {
  do_all<Q_ACCEL>(input, kernel, output);
}
