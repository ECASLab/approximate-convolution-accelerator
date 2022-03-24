#!/usr/bin/env gnuplot -p
############################################################
## Copyright 2022
## Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
############################################################

set term svg size 640, 480
set output "plot_error_".accel.".svg"

set xlabel "Datatype bit-width (bits)"
set ylabel "Mean error of the pixels"

# "${Q_KS} ${Q_BW} ${Q_O} ${IMG_RMSE} ${IMG_PSNR} ${IMG_MEAN} ${IMG_STD} ${IMG_SSIM}"
plot "stats_".accel."_3_processed_.data" u 2:6:7 smooth unique w errorlines title "K = 3", \
     "stats_".accel."_5_processed_.data" u 2:6:7 smooth unique w errorlines title "K = 5", \
     "stats_".accel."_7_processed_.data" u 2:6:7 smooth unique w errorlines title "K = 7" 

# using 2:4 with points title "K = 3"

