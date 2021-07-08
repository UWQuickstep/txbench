#ifndef TXBENCH_SRC_BENCHMARKS_TATP_TATP_WORKER_H
#define TXBENCH_SRC_BENCHMARKS_TATP_TATP_WORKER_H

#include "tatp_connection.h"
#include "utilities/worker.h"
#include <atomic>
#include <cstdlib>
#include <memory>

class TATPWorker : public Worker {
public:
  TATPWorker(size_t num_rows, std::unique_ptr<TATPConnection> connection);

  void run(std::atomic_bool &terminate,
           std::atomic_uint32_t &commit_count) override;

private:
  int num_rows_;
  int a_val_;
  std::unique_ptr<TATPConnection> connection_;
};

#endif // TXBENCH_SRC_BENCHMARKS_TATP_TATP_WORKER_H
