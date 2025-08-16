#include "competitive/algorithm/topological_sort.hpp"
#include "atcoder/dsu.hpp"
#include "random_test_base.hpp"
#include <gtest/gtest.h>

class TopologicalSortRandom : public test_utils::RandomTestBase,
                              public ::testing::WithParamInterface<int> {
  static inline std::mt19937 engine;

protected:
  std::vector<int> order;
  std::vector<std::set<int>> edge;
  static constexpr int N = 100'000;
  static constexpr int E = 200'000;

  virtual std::mt19937& get_random_engine() override {
    return engine;
  }
  virtual void SetUp() override {
    order.resize(N);
    edge.resize(N);
    std::iota(order.begin(), order.end(), 0);
    shuffle(order);
    auto dist = make_uniform_int_distribution(N - 1);
    atcoder::dsu dsu(N);
    for ([[maybe_unused]] auto _ : common::irange(N - 1)) {
      int i, j;
      do {
        i = dist();
        j = dist();
      } while (i == j || dsu.same(i, j));
      if (order[j] < order[i]) {
        std::swap(i, j);
      }
      edge[i].emplace(j);
    }
    for ([[maybe_unused]] auto _ : common::irange(N - 1, E)) {
      int i, j;
      do {
        i = dist();
        j = dist();
        if (order[j] < order[i]) {
          std::swap(i, j);
        }
      } while (i == j || edge[i].contains(j));
      edge[i].emplace(j);
    }
  }
};

TEST_P(TopologicalSortRandom, NonCycleGraph) {
  auto result = competitive::topological_sort(edge);
  ASSERT_TRUE(result);
  const auto& vec = *result;
  std::vector<int> rvec(N);
  ASSERT_EQ(vec.size(), N);
  for (auto i : common::irange(N)) {
    rvec[vec[i]] = i;
  }
  for (auto i : common::irange(N)) {
    for (auto j : edge[i]) {
      ASSERT_LT(rvec[i], rvec[j]);
    }
  }
}
TEST_P(TopologicalSortRandom, CycleGraph) {
  auto dist = make_uniform_int_distribution(N - 1);
  int s;
  do {
    s = dist();
  } while (edge[s].size() == 0);
  int e = s;
  while (edge[e].size()) {
    e = *edge[e].begin();
  };
  edge[e].emplace(s);

  auto result = competitive::topological_sort(edge);
  ASSERT_FALSE(result);
}
INSTANTIATE_TEST_CASE_P(RandomCaseTest, TopologicalSortRandom,
                        ::testing::Range(0, 20));
