#include "benchmarks/tatp/tatp_benchmark.h"
#include "../inmem_arrays_TATP_db.h"
#include "inmem_arrays_TATP_db_ART.h"
#include <iostream>
#include <memory>

#include "art_lib/art.h"


int main(int argc, char **argv) {
  auto server = std::make_unique<InMemArraysTATPServer<ArtTATPDB>>();
  std::shared_ptr<ArtTATPDB> db = server->db_;

  TATPBenchmark benchmark = TATPBenchmark::parse(argc, argv, std::move(server));
  db->init(benchmark.num_rows());
  double tps = benchmark.run();

  db->print_stats();

  std::cout << "Throughput (tps): " << tps << std::endl;

  return 0;
}
