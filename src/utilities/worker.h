#ifndef TXBENCH_SRC_UTILITIES_WORKER_H
#define TXBENCH_SRC_UTILITIES_WORKER_H

#include <atomic>
#include <cstddef>

class Worker {
public:
  Worker();
  virtual ~Worker() = default;

  size_t get_commit_count() const;

  virtual void run(std::atomic_bool &terminate,
                   std::atomic_uint32_t &commit_count) = 0;
};

#endif // TXBENCH_SRC_UTILITIES_WORKER_H
