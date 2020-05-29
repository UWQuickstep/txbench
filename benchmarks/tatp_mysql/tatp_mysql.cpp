#include "tatp_mysql_benchmark.h"
#include <iostream>

int main() {
  int n_workers = 1;
  int warmup_duration = 5;
  int measurement_duration = 10;
  int n_rows = 1000;
  txbench::TATPMySQLBenchmark benchmark(n_workers, warmup_duration,
                                        measurement_duration, n_rows);
  double tps = benchmark.run();
  std::cout << "tps: " << tps << std::endl;
}
