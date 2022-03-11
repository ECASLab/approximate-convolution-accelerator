#!/bin/bash
############################################################
## Copyright 2022
## Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
############################################################

# ksize bw o min_lat avg_lat max_lat dsp lut bram ff

# Join the consumptions for datatypes
OUTPUT="2"
KS="3 5 7"
ACCELS="Spatial Winograd"
for acc in ${ACCELS};
do
  FILE="${acc}-report.data"
  for ks in ${KS};
  do
    awk "{if (\$1 == ${ks} && \$3 == ${OUTPUT}) print \$0}" ${FILE} > "consumption_${acc}_${ks}_dtypes.data"
    gnuplot -e "accel='${acc}';ks='${ks}'" plot_datatype_consumption.plt
  done
done

# Join the consumptions for output
DATATYPE=8
for acc in ${ACCELS};
do
  FILE="${acc}-report.data"
  for ks in ${KS};
  do
    awk "{if (\$1 == ${ks} && \$2 == ${DATATYPE}) print \$0}" ${FILE} > "consumption_${acc}_${ks}_outputs.data"
    gnuplot -e "accel='${acc}';ks='${ks}'" plot_output_consumption.plt
  done
done
