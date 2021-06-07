#ifndef TXBENCH_SRC_UTILITIES_GENERATOR_H
#define TXBENCH_SRC_UTILITIES_GENERATOR_H

#include <random>

class RandomGenerator {
public:
  RandomGenerator();

  int random_int(int a, int b);
  bool random_bool();

private:
  std::mt19937 mt_;
};

#endif // TXBENCH_SRC_UTILITIES_GENERATOR_H
