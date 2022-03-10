#!/usr/bin/env gnuplot -p

set term png size 640, 480
set output "plot_hist_datatypes_".accel."_".img.".png"

set xlabel "Normalised Error (0 to 1)"
set ylabel "Scaled occurence (1/max)"

# Type Kernel_Size Min Max Mean StdDev Variance
plot "norm_hist_500_30%_".img."_4_".accel.".data" u ($0*0.3/500):($1) w l title "W = 4", \
     "norm_hist_500_30%_".img."_6_".accel.".data" u ($0*0.3/500):($1) w l title "W = 6", \
     "norm_hist_500_30%_".img."_8_".accel.".data" u ($0*0.3/500):($1) w l title "W = 8", \
     "norm_hist_500_30%_".img."_10_".accel.".data" u ($0*0.3/500):($1) w l title "W = 10", \
     "norm_hist_500_30%_".img."_12_".accel.".data" u ($0*0.3/500):($1) w l title "W = 12", \
     "norm_hist_500_30%_".img."_14_".accel.".data" u ($0*0.3/500):($1) w l title "W = 14", \
     "norm_hist_500_30%_".img."_16_".accel.".data" u ($0*0.3/500):($1) w l title "W = 16"
