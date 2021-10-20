# Approximate Convolution Accelerator

## Software version

### Compiling

For compiling the code, no-dependencies are needed so far. You may only need the `meson` building system. Please, follow these steps to get it into your system:

```bash
sudo apt update
sudo apt install python3 python3-pip ninja-build
sudo pip3 install meson
sudo apt install openmpi-common libopenmpi2
pip3 install matplotlib numpy
```

After installing the building system, compile the code:

```bash
meson builddir
ninja -C builddir
```

### Testing

You can test the code by using:

```bash
cd builddir/tests/sw-ops
./convolution # For spatial convolution
```

## Hardware version

For the hardware version, you will need Vivado HLS 2018.2.

You can run the tests in the following way:

```bash
# Run a synthesis + simulation
cd tests/hw-ops/
TEST=spatialconv make test

# Run everything - with a Kernel Size of 3x3
export Q_KS=3
make measure-all

# Extracts data
make extract-data

# Clean all
make clean
```

where the possible targets are:

* test: performs the tests on a given testbench
* measure: synthesises, runs and extracts the logs for measurement
* measure-all: runs all the synthesis and simulations
* extract-data: cleans the logs, recompiling just the useful information

and where the environment variables are:

* TEST: name of the tests. Please, inspect `tests/hw-ops/tops/*.cpp` for the possible tests. You can also use `make help`.
* Q_KS: Kernel size (one of the sides). Default: 3
* Q_BW: Bit length of the integer logarithm representation. Default: 8
* SYN_TOOL: name of the synthesis tool. By default, it is `vivado_hls`

> If something fails and it is related to `vivado_hls not found`, please, make sure of having it in the environment. Usually, it requires:
> `source /opt/Xilinx/Vivado/2018.2/settings64.sh`

## Important data

After the extraction, the relevant files are:

```
test/hw-ops/measurements/
  |_ *-report.data      -> Report about latency and resources
  |_ *-maxerrs_*.data   -> Report about the maximum error reported
```

## How to add a new hardware testbench

1. Create a directive file: you can simply copy and paste one of the existing in `directives/`. The syntax is: `${TEST}.tcl`.
2. Create the top files: they are in `tops/`. The filenames must match the following syntax: `${TEST}.cpp` and `${TEST}.hpp`.
3. The top function must follow the syntax: `${TEST}_top_accel`.
4. Create a testbench. The testbench file must be named as `${TEST}_tb.cpp`.
5. Add the test to `helpers/measure-all.sh` to `ACCELS`. For example:
`ACCELS=${ACCELS:-"spatialconv winograd"}`, where `winograd` is a new test.

Author:

* Alejandro Rodriguez Figueroa <alejandrorf@estudiantec.cr>
* Luis G. Leon Vega <lleon95@estudiantec.cr>
