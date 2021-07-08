#ifndef TXBENCH_SRC_BENCHMARKS_TATP_TATP_SERVER_H
#define TXBENCH_SRC_BENCHMARKS_TATP_TATP_SERVER_H

#include "tatp_connection.h"
#include <memory>

class TATPServer {
public:
  virtual ~TATPServer() = default;
  virtual std::unique_ptr<TATPConnection> connect() = 0;
};

#endif // TXBENCH_SRC_BENCHMARKS_TATP_TATP_SERVER_H
