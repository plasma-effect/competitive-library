#include "graph/topological_sort.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

TEST(TopologicalSort, ExecuteSizeT) {
  const int N = 5;
  std::vector<std::set<std::size_t>> edge(N);
  edge[0].emplace(3);
  edge[0].emplace(4);
  edge[1].emplace(2);
  edge[1].emplace(4);
  edge[2].emplace(3);
  edge[2].emplace(4);
  auto result = graph::topological_sort(edge);
  EXPECT_TRUE(result);
  const auto vec = *result;
  for (std::size_t i : common::irange(N)) {
    for (auto n : edge[i]) {
      auto a = std::ranges::find(vec, i);
      auto b = std::ranges::find(vec, n);
      EXPECT_LT(a, b) << "(i, n) = (" << i << ", " << n << ")";
    }
  }
}

TEST(TopologicalSort, ExecuteInt) {
  const int N = 5;
  std::vector<std::set<int>> edge(N);
  edge[0].emplace(3);
  edge[0].emplace(4);
  edge[1].emplace(2);
  edge[1].emplace(4);
  edge[2].emplace(3);
  edge[2].emplace(4);
  auto result = graph::topological_sort(edge);
  EXPECT_TRUE(result);
  const auto vec = *result;
  for (int i : common::irange(N)) {
    for (auto n : edge[i]) {
      auto a = std::ranges::find(vec, i);
      auto b = std::ranges::find(vec, n);
      EXPECT_LT(a, b) << "(i, n) = (" << i << ", " << n << ")";
    }
  }
}

TEST(TopologicalSort, DetectCycle) {
  const int N = 3;
  std::vector<std::set<int>> edge(N);
  edge[0].emplace(1);
  edge[1].emplace(2);
  edge[2].emplace(0);
  auto result = graph::topological_sort(edge);
  EXPECT_FALSE(result);
}

class TopologicalSortRandom : public test_utils::RandomTestBase,
                              public ::testing::WithParamInterface<int> {
  static inline std::mt19937 engine;

protected:
  std::vector<int> order;
  std::vector<std::set<int>> edge;
  static constexpr int N = 100'000;
  static constexpr int E = 200'000;

  virtual std::mt19937& get_random_engine() override { return engine; }
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
  auto result = graph::topological_sort(edge);
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

  auto result = graph::topological_sort(edge);
  ASSERT_FALSE(result);
}
INSTANTIATE_TEST_CASE_P(RandomCaseTest, TopologicalSortRandom,
                        ::testing::Range(0, 20));
