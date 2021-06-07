#ifndef TXBENCH_SRC_UTILITIES_BENCHMARK_H
#define TXBENCH_SRC_UTILITIES_BENCHMARK_H

#include "worker.h"
#include <cstdlib>
#include <memory>

class Benchmark {
public:
  Benchmark(size_t num_workers, size_t warmup_duration,
            size_t measure_duration);

  double run();

protected:
  virtual void load() = 0;
  virtual std::unique_ptr<Worker> make_worker() = 0;

private:
  size_t num_workers_;
  size_t warmup_duration_;
  size_t measure_duration_;
};

#endif // TXBENCH_SRC_UTILITIES_BENCHMARK_H
