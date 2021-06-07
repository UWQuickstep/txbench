#include "tatp_benchmark.h"

#include "tatp_worker.h"
#include "utilities/options.h"
#include <memory>

TATPBenchmark::TATPBenchmark(std::unique_ptr<TATPServer> server,
                             size_t num_rows, size_t num_workers,
                             size_t warmup_duration, size_t measure_duration)
    : Benchmark(num_workers, warmup_duration, measure_duration),
      server_(std::move(server)), num_rows_(num_rows) {}

TATPBenchmark TATPBenchmark::parse(int argc, char **argv,
                                   std::unique_ptr<TATPServer> server) {
  Options options("tatp", "The TATP benchmark");

  options.add<size_t>("num_rows", "Number of rows in the Subscriber table",
                      true);
  options.add<size_t>("num_workers", "Number of worker threads", true);
  options.add<bool>("load", "Load the benchmark data (default: false)", false);
  options.add<size_t>("warmup_duration",
                      "Warmup duration in seconds (default: 10)", false);
  options.add<size_t>("measure_duration",
                      "Measure duration in seconds (default: 60)", false);

  ParseResult result = options.parse(argc, argv);

  size_t num_rows = result["num_rows"].as<size_t>();
  size_t num_workers = result["num_workers"].as<size_t>();

  bool load = false;
  if (result.count("load")) {
    load = true;
  }

  size_t warmup_duration = 10;
  if (result.count("warmup_duration")) {
    warmup_duration = result["warmup_duration"].as<size_t>();
  }

  size_t measure_duration = 60;
  if (result.count("measure_duration")) {
    measure_duration = result["measure_duration"].as<size_t>();
  }

  return TATPBenchmark(std::move(server), num_rows, num_workers,
                       warmup_duration, measure_duration);
}

void TATPBenchmark::load() { server_->load(); }

std::unique_ptr<Worker> TATPBenchmark::make_worker() {
  return std::make_unique<TATPWorker>(num_rows_, server_->connect());
}
