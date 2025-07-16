#include "competitive/heuristic/persistent_array.hpp"
#include "random_test_base.hpp"
#include <gtest/gtest.h>

class PersistentArrayRandom : public test_utils::RandomTestBase,
                              public ::testing::WithParamInterface<int> {
  static inline std::mt19937 engine;

protected:
  virtual std::mt19937& get_random_engine() override {
    return engine;
  }
};

static constexpr int N = 1 << 12;
using array_t = heuristic::persistent_array<int, N>;
TEST_P(PersistentArrayRandom, UpdateOld) {
  constexpr std::size_t U = 1;
  std::array<int, N> current{};
  array_t ar;
  std::vector<std::pair<int, array_t>> results;
  auto dist = make_uniform_int_distribution(1, 0xFF);
  for (std::size_t idx = 0, c = 0; c < N / U; ++c) {
    for (std::size_t u = 0; u < U; ++u, idx += 3) {
      auto i = idx & (N - 1);
      current[i] = dist();
      ar.update(i, current[i]);
    }
    int sum = std::accumulate(current.begin(), current.end(), 0);
    results.emplace_back(sum, ar);
  }
  for (auto const& [sum, par] : results) {
    int psum = 0;
    for (auto i = 0uz; i < N; ++i) {
      psum += par.get(i);
    }
    ASSERT_EQ(psum, sum);
  }
}

TEST_P(PersistentArrayRandom, UpdateNew) {
  constexpr std::size_t U = 1;
  std::array<int, N> current{};
  std::vector<std::pair<int, array_t>> results(1);
  auto dist = make_uniform_int_distribution(1, 0xFF);
  for (std::size_t idx = 0, c = 0; c < N / U; ++c) {
    auto ar = results.back().second;
    for (std::size_t u = 0; u < U; ++u, idx += 3) {
      auto i = idx & (N - 1);
      current[i] = dist();
      ar.update(i, current[i]);
    }
    int sum = std::accumulate(current.begin(), current.end(), 0);
    results.emplace_back(sum, ar);
  }
  for (auto const& [sum, par] : results) {
    int psum = 0;
    for (auto i = 0uz; i < N; ++i) {
      psum += par.get(i);
    }
    ASSERT_EQ(psum, sum);
  }
}

INSTANTIATE_TEST_CASE_P(RandomCaseTest, PersistentArrayRandom,
                        ::testing::Range(0, 20));
