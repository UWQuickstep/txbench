#include "tatp_util.h"

#include <random>

std::string leading_zero_pad(size_t length, const std::string &s) {
  assert(length >= s.length());
  return std::string(length - s.length(), '0') + s;
}

std::string uppercase_string(size_t length, RandomGenerator &rg) {
  static std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  static std::uniform_int_distribution<size_t> dis(0, chars.size() - 1);

  std::string s(length, 0);
  std::generate(s.begin(), s.end(),
                [&] { return chars[rg.random_size_t(0, chars.size() - 1)]; });

  return s;
}
