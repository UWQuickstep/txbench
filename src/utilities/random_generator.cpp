#include "random_generator.h"

RandomGenerator::RandomGenerator() : mt_(std::random_device()()) {}

int RandomGenerator::random_int(int a, int b) {
  std::uniform_int_distribution<int> dis(a, b);
  return dis(mt_);
}

size_t RandomGenerator::random_size_t(size_t a, size_t b) {
  std::uniform_int_distribution<size_t> dis(a, b);
  return dis(mt_);
}

bool RandomGenerator::random_bool() { return random_int(0, 1); }

std::mt19937 &RandomGenerator::mt() { return mt_; }

int32_t RandomNonUniSid(int A, int size) {
  auto a =
      ((RandomValue<int32_t>(0, A) | RandomValue<int32_t>(0, size - 1))
          % (size - 1 - 0 + 1));
  return a;
}

int calculateNonUniformA(int size) {
  int A = 0;
  if (size <= 1'000'000) {
    A = 65535;
  } else if (size <= 10'000'000) {
    A = 1048575;
  } else {
    A = 2097151;
  }
  return A;
}
