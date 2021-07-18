#include "benchmarks/tatp/tatp_benchmark.h"
#include "../inmem_arrays_TATP_db.h"
#include "inmem_arrays_TATP_db_TLX.h"
#include <iostream>
#include <memory>

#include "alex_lib/alex.h"


int main(int argc, char **argv) {
  auto server = std::make_unique<InMemArraysTATPServer<AlexTATPDB>>();
  std::shared_ptr<AlexTATPDB> db = server->db_;

  TATPBenchmark benchmark = TATPBenchmark::parse(argc, argv, std::move(server));
  db->init(benchmark.num_rows());
  double tps = benchmark.run();

  db->print_stats();

  std::cout << "Throughput (tps): " << tps << std::endl;

  return 0;
}