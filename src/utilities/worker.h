#ifndef TXBENCH_SRC_UTILITIES_WORKER_H
#define TXBENCH_SRC_UTILITIES_WORKER_H

#include <atomic>

class Worker {
public:
  Worker();
  virtual ~Worker() = default;

  size_t get_commit_count() const;

  virtual void run(std::atomic_bool &terminate) = 0;

protected:
  std::atomic_size_t commit_count_;
};

#endif // TXBENCH_SRC_UTILITIES_WORKER_H
