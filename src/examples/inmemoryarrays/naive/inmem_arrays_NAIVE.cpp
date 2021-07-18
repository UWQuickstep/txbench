#include "benchmarks/tatp/tatp_benchmark.h"
#include "../inmem_arrays_TATP_db.h"
//#include "inmem_arrays_TATP_db_PALM.h"
//#include "inmem_arrays_TATP_db_ALEX.h"
#include <iostream>
#include <memory>

//#include "alex/alex.h"


int main(int argc, char **argv) {
  auto server = std::make_unique<InMemArraysTATPServer<InMemArraysTATPDB>>();
  std::shared_ptr<InMemArraysTATPDB> db = server->db_;

  TATPBenchmark benchmark = TATPBenchmark::parse(argc, argv, std::move(server));
  double tps = benchmark.run();

  db->print_stats();

  std::cout << "Throughput (tps): " << tps << std::endl;

  return 0;
}
