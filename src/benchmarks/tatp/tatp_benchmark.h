#ifndef TXBENCH_SRC_BENCHMARKS_TATP_TATP_BENCHMARK_H
#define TXBENCH_SRC_BENCHMARKS_TATP_TATP_BENCHMARK_H

#include "tatp_server.h"
#include "utilities/benchmark.h"
#include <cstdlib>
#include <memory>

class TATPBenchmark : public Benchmark {
public:
  TATPBenchmark(std::unique_ptr<TATPServer> server, size_t num_rows,
                size_t num_workers, size_t warmup_duration,
                size_t measure_duration);

  static TATPBenchmark parse(int argc, char **argv,
                             std::unique_ptr<TATPServer> server);

protected:
  void load() override;
  std::unique_ptr<Worker> make_worker() override;

private:
  std::unique_ptr<TATPServer> server_;
  size_t num_rows_;
};

#endif // TXBENCH_SRC_BENCHMARKS_TATP_TATP_BENCHMARK_H
