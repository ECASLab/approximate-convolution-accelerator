#!/bin/bash
############################################################
## Copyright 2021
## Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
############################################################

let CID=${OMPI_COMM_WORLD_RANK:-0}
let SIZE=${OMPI_COMM_WORLD_SIZE:-1}

# Q_KS limits
MIN_Q_K=${MIN_Q_K:-3}
MAX_Q_K=${MAX_Q_K:-7} # 16
STEP_Q_K=${STEP_Q_K:-2}

# Output
MIN_Q_O=${MIN_Q_O:-2}
MAX_Q_O=${MAX_Q_O:-4} # 16
STEP_Q_O=${STEP_Q_O:-2}

# Q_BW limits
MIN_Q_BW=${MIN_Q_BW:-4}
MAX_Q_BW=${MAX_Q_BW:-8} #16
STEP_Q_BW=${STEP_Q_BW:-2}

# Accelerators - Discretised because of Bash limitations in unrolling
ACCELS=${ACCELS:-"Winograd Spatial"}

# Offsets
START_IDX=$((${CID}*${STEP_Q_BW}+${MIN_Q_BW}))
END_IDX=${MAX_Q_BW}
STEP_IDX=$((${STEP_Q_BW}*${SIZE}))

# Compute the boundaries in BitWidth
for i in $(seq ${START_IDX} ${STEP_IDX} ${END_IDX});
do
  for accel in ${ACCELS};
  do
    for ks in $(seq ${MIN_Q_K} ${STEP_Q_K} ${MAX_Q_K});
    do
      for o in $(seq ${MIN_Q_O} ${STEP_Q_O} ${MAX_Q_O});
      do
        echo "[Measuring all]: Computing ${accel} with BW ${i}, QO ${o} and KS ${ks} in processor ${CID}"
        Q_O=${o} Q_KS=${ks} Q_BW=${i} Q_CONV_CORE=${accel} TEST=single_core CUSTOM_FLAGS=-DOVERRIDE_TH make measure
      done
    done
  done
done
