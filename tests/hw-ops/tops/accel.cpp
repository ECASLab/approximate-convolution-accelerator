/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include "accel.hpp"

/*
  [RO] The number of PEs
  [RO] Datatype. By default, it should be fixed-point.
  [RO] Number of bits of the datatype. By default, 8 bits with 1 bit of sign
  [RO] Normalisation type. By default, it should be pass-thru
  [RO] Kernel size (it can be NXN). By default, it should be 3x3
  [RO] Scaling. By default, it is not scaled.
  [RO] Pooling. By default, it is not pooled.
  [RW] Image width
  [RW] Image height
  [RW] Kernel[]. By default, it is an impulse.
*/

/* The convolution happens in row-major but it is transferred by columns */
void accel_top_accel(DataType input[kRowsWindow][kWindowSize],
                     DataType kernel[kKernelSize][kKernelSize],
                     DataType output[kRowsOutput][kOutputSize],
                     PropertyPort &npes, PropertyPort &datatype,
                     PropertyPort &bitwidth, PropertyPort &normalisation,
                     PropertyPort &kernelsize, PropertyPort &scaling,
                     PropertyPort &pooling, DimensionPort &in_width,
                     DimensionPort &in_height, DimensionPort &out_width,
                     DimensionPort &out_height) {
#pragma HLS INTERFACE m_axi depth = 256 register offset = slave port = \
    input bundle = datamem
#pragma HLS INTERFACE m_axi depth = 256 register offset = slave port = \
    output bundle = datamem
#pragma HLS INTERFACE s_axilite register port = kernel offset = \
    0x0010 bundle = control
#pragma HLS INTERFACE s_axilite register port = return bundle = control
/* Common */
#pragma HLS INTERFACE s_axilite register port = npes offset = 0x0010 bundle = \
    control
#pragma HLS INTERFACE s_axilite register port = datatype offset = \
    0x0018 bundle = control
#pragma HLS INTERFACE s_axilite register port = bitwidth offset = \
    0x0020 bundle = control
/* Convolution specific */
#pragma HLS INTERFACE s_axilite register port = normalisation offset = \
    0x0100 bundle = control
#pragma HLS INTERFACE s_axilite register port = kernelsize offset = \
    0x0108 bundle = control
#pragma HLS INTERFACE s_axilite register port = scaling offset = \
    0x0110 bundle = control
#pragma HLS INTERFACE s_axilite register port = pooling offset = \
    0x0118 bundle = control
/* Dimensionality */
#pragma HLS INTERFACE s_axilite register port = in_width offset = \
    0x0200 bundle = control
#pragma HLS INTERFACE s_axilite register port = in_height offset = \
    0x0208 bundle = control
#pragma HLS INTERFACE s_axilite register port = out_width offset = \
    0x0300 bundle = control
#pragma HLS INTERFACE s_axilite register port = out_height offset = \
    0x0308 bundle = control

  /* Set properties */
  npes = Q_ACCEL;
  datatype = 0;
  bitwidth = Q_BW;
  normalisation = 1;
  kernelsize = Q_K;
  scaling = 1;
  pooling = 1;
  out_width = kOutputSize;
  out_height = kRowsOutput;
  in_width = kRowsWindow;
  in_height = kWindowSize;

  using Engine = ama::hw::convolvers::Spatial<DataType, Q_K, Q_O>;
  ama::hw::ParallelConvolver<Q_ACCEL, Q_ACCEL, Engine>::Execute(input, kernel,
                                                                output);
}
