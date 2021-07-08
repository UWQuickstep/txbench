#ifndef TXBENCH_SRC_UTILITIES_GENERATOR_H
#define TXBENCH_SRC_UTILITIES_GENERATOR_H

#include <random>
#include <unordered_set>

class RandomGenerator {
public:
  RandomGenerator();

  int random_int(int a, int b);
  size_t random_size_t(size_t a, size_t b);
  bool random_bool();
  std::mt19937 &mt();

private:
  std::mt19937 mt_;
};


template<typename Type>
int RandomValue(int64_t min, int64_t max) {
  return static_cast<Type>(rand() % (max - min + 1) + min);
}

template<typename Type>
std::vector<Type> UniqueRandomValues(int min, int max, int n) {
  std::vector<Type> res;
  if (n == (max - min + 1)) {
    for (int i = min; i <= max; ++i) {
      res.push_back(static_cast<Type>(i));
    }
    return res;
  }
  std::unordered_set<Type> set;
  while (set.size() < n) {
    int rv = RandomValue<Type>(min, max);
    auto exists = set.find(rv);
    if (exists == set.end()) {
      set.emplace(rv);
      res.push_back(static_cast<Type>(rv));
    }
  }
  return res;
}

template<typename type, size_t size>
std::array<type, size> randIntArray(int min, int max) {
  std::array<type, size> r;
  for (int i = 0; i < size - 1; ++i) {
    r[i] = RandomValue<type>(min, max);
  }
  return r;
}

template<size_t size>
std::array<char, size> randAZCharArray() {
  std::array<char, size> r;
  for (int i = 0; i < size - 1; ++i) {
    r[i] = 'A' + RandomValue<int>(0, 25);
  }
  return r;
}

int32_t RandomNonUniSid(int A, int size);

int calculateNonUniformA(int size);

#endif // TXBENCH_SRC_UTILITIES_GENERATOR_H
