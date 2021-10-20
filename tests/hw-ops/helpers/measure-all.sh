#!/bin/bash
############################################################
## Copyright 2021
## Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
############################################################

let CID=${OMPI_COMM_WORLD_RANK:-0}
let SIZE=${OMPI_COMM_WORLD_SIZE:-1}

# Q_KS limits
Q_KS=${Q_KS:-3}

# Q_BW limits
MIN_Q_BW=${MIN_Q_BW:-4}
MAX_Q_BW=${MAX_Q_BW:-8}
STEP=${STEP_Q_BW:-4}

# Accelerators - Discretised because of Bash limitations in unrolling
ACCELS=${ACCELS:-"spatialconv"}

# Offsets
START_IDX=$((${CID}*${STEP}+${MIN_Q_BW}))
STEP_IDX=$((${STEP}*${SIZE}))

# Compute the boundaries in BitWidth
for i in $(seq ${START_IDX} ${STEP_IDX} ${MAX_Q_BW});
do
  for accel in ${ACCELS};
  do
    echo "[Measuring all]: Computing ${accel} with BW ${i} and R ${Q_KS} in processor ${CID}"
    Q_KS=${Q_KS} Q_BW=${i} TEST=${accel} CUSTOM_FLAGS=-DOVERRIDE_TH make measure
  done
done
