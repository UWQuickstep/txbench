#ifndef TXBENCH_SRC_BENCHMARKS_TATP_TATP_UTIL_H
#define TXBENCH_SRC_BENCHMARKS_TATP_TATP_UTIL_H

#include "utilities/random_generator.h"
#include <string>

std::string leading_zero_pad(size_t length, const std::string &s);
std::string uppercase_string(size_t length, RandomGenerator &rg);

#endif // TXBENCH_SRC_BENCHMARKS_TATP_TATP_UTIL_H
