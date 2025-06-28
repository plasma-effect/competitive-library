#include "data_structure/min_max_heap.hpp"
#include <gtest/gtest.h>

namespace {
struct uncopyable {
  std::uint32_t v;
  uncopyable(std::uint32_t u) : v(u) {}
  uncopyable(uncopyable const&) = delete;
  uncopyable& operator=(uncopyable const&) = delete;
  uncopyable(uncopyable&&) = default;
  uncopyable& operator=(uncopyable&&) = default;

  bool operator<(uncopyable const& a) const {
    return v < a.v;
  }
  bool operator==(std::uint32_t u) const {
    return v == u;
  }
};
} // namespace

TEST(DataStructure, MinMaxHeapGeneral) {
  competitive::min_max_heap<int> heap;
  EXPECT_EQ(heap.size(), 0);

  heap.push(2);
  EXPECT_EQ(heap.min(), 2);
  EXPECT_EQ(heap.max(), 2);

  heap.push(1);
  EXPECT_EQ(heap.min(), 1);
  EXPECT_EQ(heap.max(), 2);

  heap.push(3);
  EXPECT_EQ(heap.min(), 1);
  EXPECT_EQ(heap.max(), 3);

  heap.push(0);
  EXPECT_EQ(heap.min(), 0);
  EXPECT_EQ(heap.max(), 3);

  heap.push(4);
  EXPECT_EQ(heap.min(), 0);
  EXPECT_EQ(heap.max(), 4);
}

TEST(DataStructure, MinMaxHeapPopMin) {
  competitive::min_max_heap<int> heap;
  for (int i : common::irange(31)) {
    heap.push(i);
  }
  for (int i : common::irange(1, 31)) {
    heap.pop_min();
    EXPECT_EQ(heap.min(), i);
  }
  heap.pop_min();
  EXPECT_EQ(heap.size(), 0);
}

TEST(DataStructure, MinMaxHeapPopMax) {
  competitive::min_max_heap<int> heap;
  for (int i : common::irange(31)) {
    heap.push(i);
  }
  for (int i : common::irange(30) | std::views::reverse) {
    heap.pop_max();
    EXPECT_EQ(heap.max(), i);
  }
  heap.pop_max();
  EXPECT_EQ(heap.size(), 0);
}

TEST(DataStructure, MinMaxHeapPopMinMax) {
  competitive::min_max_heap<int> heap;
  for (int i : common::irange(31)) {
    heap.push(i);
  }
  for (int i : common::irange(1, 16)) {
    heap.pop_min();
    heap.pop_max();
    EXPECT_EQ(heap.min(), i);
    EXPECT_EQ(heap.max(), 30 - i);
  }
  heap.pop_min();
  EXPECT_EQ(heap.size(), 0);
}

TEST(DataStructure, MinMaxHeapCustomProj) {
  competitive::min_max_heap<common::pair<int>> heap(
      [](common::pair<int> const& p) { return p.first + p.second; });
  heap.emplace(2, 4);
  EXPECT_EQ(heap.min(), std::pair(2, 4));
  EXPECT_EQ(heap.max(), std::pair(2, 4));

  heap.emplace(3, 2);
  EXPECT_EQ(heap.min(), std::pair(3, 2));
  EXPECT_EQ(heap.max(), std::pair(2, 4));

  heap.emplace(1, 6);
  EXPECT_EQ(heap.min(), std::pair(3, 2));
  EXPECT_EQ(heap.max(), std::pair(1, 6));

  heap.emplace(4, 0);
  EXPECT_EQ(heap.min(), std::pair(4, 0));
  EXPECT_EQ(heap.max(), std::pair(1, 6));

  heap.emplace(0, 8);
  EXPECT_EQ(heap.min(), std::pair(4, 0));
  EXPECT_EQ(heap.max(), std::pair(0, 8));
}

TEST(DataStructure, MinMaxHeapUnCopyable) {
  competitive::min_max_heap<uncopyable> heap;
  EXPECT_EQ(heap.size(), 0);

  heap.push(uncopyable(2));
  EXPECT_EQ(heap.min(), 2);
  EXPECT_EQ(heap.max(), 2);

  heap.push(uncopyable(1));
  EXPECT_EQ(heap.min(), 1);
  EXPECT_EQ(heap.max(), 2);

  heap.push(uncopyable(3));
  EXPECT_EQ(heap.min(), 1);
  EXPECT_EQ(heap.max(), 3);

  heap.push(uncopyable(0));
  EXPECT_EQ(heap.min(), 0);
  EXPECT_EQ(heap.max(), 3);

  heap.push(uncopyable(4));
  EXPECT_EQ(heap.min(), 0);
  EXPECT_EQ(heap.max(), 4);
}

TEST(DataStructure, MinMaxHeapUnCopyablePopMin) {
  competitive::min_max_heap<uncopyable> heap;
  for (int i : common::irange(31)) {
    heap.push(uncopyable(i));
  }
  for (int i : common::irange(1, 31)) {
    heap.pop_min();
    EXPECT_EQ(heap.min(), i);
  }
  heap.pop_min();
  EXPECT_EQ(heap.size(), 0);
}

TEST(DataStructure, MinMaxHeapUnCopyablePopMax) {
  competitive::min_max_heap<uncopyable> heap;
  for (int i : common::irange(31)) {
    heap.push(uncopyable(i));
  }
  for (int i : common::irange(30) | std::views::reverse) {
    heap.pop_max();
    EXPECT_EQ(heap.max(), i);
  }
  heap.pop_max();
  EXPECT_EQ(heap.size(), 0);
}

TEST(DataStructure, MinMaxHeapUnCopyablePopMinMax) {
  competitive::min_max_heap<uncopyable> heap;
  for (int i : common::irange(31)) {
    heap.push(uncopyable(i));
  }
  for (int i : common::irange(1, 16)) {
    heap.pop_min();
    heap.pop_max();
    EXPECT_EQ(heap.min(), i);
    EXPECT_EQ(heap.max(), 30 - i);
  }
  heap.pop_max();
  EXPECT_EQ(heap.size(), 0);
}

TEST(DataStructure, MinMaxHeapUnCopyableCustomProj) {
  competitive::min_max_heap<uncopyable> heap(
      [](uncopyable const& p) { return std::popcount(p.v); });
  heap.emplace(0b0'00'111'0000'00000);
  EXPECT_EQ(heap.min(), 0b0'00'111'0000'00000);
  EXPECT_EQ(heap.max(), 0b0'00'111'0000'00000);

  heap.emplace(0b0'11'000'0000'00000);
  EXPECT_EQ(heap.min(), 0b0'11'000'0000'00000);
  EXPECT_EQ(heap.max(), 0b0'00'111'0000'00000);

  heap.emplace(0b0'00'000'1111'00000);
  EXPECT_EQ(heap.min(), 0b0'11'000'0000'00000);
  EXPECT_EQ(heap.max(), 0b0'00'000'1111'00000);

  heap.emplace(0b1'00'000'0000'00000);
  EXPECT_EQ(heap.min(), 0b1'00'000'0000'00000);
  EXPECT_EQ(heap.max(), 0b0'00'000'1111'00000);

  heap.emplace(0b0'00'000'0000'11111);
  EXPECT_EQ(heap.min(), 0b1'00'000'0000'00000);
  EXPECT_EQ(heap.max(), 0b0'00'000'0000'11111);
}
