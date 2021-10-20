############################################################
## Copyright 2021
## Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
############################################################

# Set your custom C-flags here
# For example:
Q_KS ?= 3
Q_BW ?= 8
CUSTOM_FLAGS+=-DQ_KS=$(Q_KS) -DQ_BW=$(Q_BW)
export CUSTOM_FLAGS Q_KS Q_BW
