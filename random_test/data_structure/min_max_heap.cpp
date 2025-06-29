#include "competitive/data_structure/min_max_heap.hpp"
#include "random_test_base.hpp"
#include <gtest/gtest.h>

class MinMaxHeapRandom : public test_utils::RandomTestBase,
                         public ::testing::WithParamInterface<int> {
  static inline std::mt19937 engine;

protected:
  std::vector<int> order;
  std::vector<common::pair<int>> forward_min_max;
  static constexpr int N = 100'000;
  virtual std::mt19937& get_random_engine() override {
    return engine;
  }
  virtual void SetUp() override {
    order.resize(N);
    forward_min_max.reserve(N);
    std::iota(order.begin(), order.end(), 0);
    shuffle(order);
    int min = common::max_v<int>, max = common::min_v<int>;
    for (auto v : order) {
      min = std::min(min, v);
      max = std::max(max, v);
      forward_min_max.emplace_back(min, max);
    }
  }
};

TEST_P(MinMaxHeapRandom, RandomPermutation) {
  competitive::min_max_heap<int> heap;
  for (auto i : common::irange(N)) {
    heap.push(order[i]);
    auto [min, max] = forward_min_max[i];
    ASSERT_EQ(heap.min(), min);
    ASSERT_EQ(heap.max(), max);
  }
  ASSERT_EQ(heap.min(), 0);
  ASSERT_EQ(heap.max(), N - 1);

  auto dist = make_uniform_int_distribution(0, 1);
  for (int min = 0, max = N - 1;
       [[maybe_unused]] auto _ : common::irange(N - 1)) {
    if (dist()) {
      heap.pop_min();
      ++min;
      ASSERT_EQ(heap.min(), min);
    } else {
      heap.pop_max();
      --max;
      ASSERT_EQ(heap.max(), max);
    }
  }
}
INSTANTIATE_TEST_CASE_P(RandomCaseTest, MinMaxHeapRandom,
                        ::testing::Range(0, 20));
