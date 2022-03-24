#!/bin/bash

# Compute the maximum and then, divide
for file in $(ls hist_*);
do
  # Normalising
  echo "Normalising: ${file}"
  MAX=$(awk 'NR==1{max = $1 + 0; next} {if ($1 > max) max = $1;} END {print max}' ${file})
  awk "{print \$1/${MAX}}" ${file} > norm_${file}
done

# Compute the histograms for every accel and image
IMGS="baboon barbara lenna peppers"
ACCELS="Winograd Spatial"
for img in ${IMGS};
do
  for acc in ${ACCELS};
  do
    gnuplot -e "img='${img}'; accel='${acc}'" plot_hist_datatypes.plt
  done
done
