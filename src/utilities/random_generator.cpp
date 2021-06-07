#include "random_generator.h"

RandomGenerator::RandomGenerator() : mt_(std::random_device()()) {}

int RandomGenerator::random_int(int a, int b) {
  std::uniform_int_distribution<int> dis(a, b);
  return dis(mt_);
}

bool RandomGenerator::random_bool() { return random_int(0, 1); }
