# txbench
A small benchmarking library for OLTP database systems

## Overview
The aim of txbench is to provide extensible benchmarking utilities for OLTP database systems. It is particularly useful for testing systems in the early stages of development that may not yet have a well-defined client interface such as a SQL interpreter. Instead, systems must simply implement C++ functions that represent the workload's procedures.

## Evaluating a target system
The steps to evaluate a target system are the following.
1. Implement the benchmark connection by extending the corresponding `Connection` class.
2. Implement the benchmark server by extending the corresponding `Server` class.
3. Create a new executable that instantiates and runs the benchmark with the server. 

For help on the executable's command line arguments, run the executable with the flag `--help`. Example servers that simply write procedure calls to stdout may be found in `src/examples/stdout`.

## Currently supported benchmarks
Currently, txbench only supports the TATP benchmark. More benchmarks and systems will be added in the future.
