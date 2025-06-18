#pragma once
#include "gtest/gtest.h"
#include <algorithm>
#include <random>

namespace test_utils {
class RandomTestBase : public testing::Test {
protected:
  virtual std::mt19937& get_random_engine() = 0;
  template <std::integral Int> auto make_uniform_int_distribution(Int max) {
    return [dist = std::uniform_int_distribution<Int>(0, max),
            &engine = get_random_engine()]() mutable {
      return dist(engine);
    };
  }
  template <std::integral Int>
  auto make_uniform_int_distribution(Int min, Int max) {
    return [dist = std::uniform_int_distribution(min, max),
            &engine = get_random_engine()]() mutable {
      return dist(engine);
    };
  }
  template <typename T> void shuffle(std::vector<T>& vec) {
    std::ranges::shuffle(vec, get_random_engine());
  }
};
} // namespace test_utils
