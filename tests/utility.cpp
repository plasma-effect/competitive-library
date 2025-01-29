#include "utility.hpp"
#include <gtest/gtest.h>

TEST(Utility, Irange1Arg) {
  std::vector vec = {0, 1, 2, 3, 4};
  ASSERT_TRUE(std::ranges::equal(vec, common::irange(5)));
}

TEST(Utility, Irange2Args) {
  std::vector vec = {3, 4, 5, 6, 7};
  ASSERT_TRUE(std::ranges::equal(vec, common::irange(3, 8)));
}

TEST(Utility, IrangeReverse) {
  std::vector vec = {4, 3, 2, 1, 0};
  ASSERT_TRUE(std::ranges::equal(vec, common::irange(5) | std::views::reverse));
}

TEST(Utility, DualArrayAssignAndRead) {
  common::dual_array<int> ar(2, 3);
  ar(0, 0) = 0;
  ar(0, 1) = 1;
  ar(0, 2) = 2;
  ar(1, 0) = 3;
  ar(1, 1) = 4;
  ar(1, 2) = 5;
  ASSERT_EQ(ar(0, 0), 0);
  ASSERT_EQ(ar(0, 1), 1);
  ASSERT_EQ(ar(0, 2), 2);
  ASSERT_EQ(ar(1, 0), 3);
  ASSERT_EQ(ar(1, 1), 4);
  ASSERT_EQ(ar(1, 2), 5);
}

TEST(Utility, DualArrayGetDimensions) {
  common::dual_array<int> ar(2, 3);
  auto [d0, d1] = ar.dimensions();
  ASSERT_EQ(d0, 2u);
  ASSERT_EQ(d1, 3u);
}

TEST(Utility, DualArrayGetSize) {
  common::dual_array<int> ar(2, 3);
  ASSERT_EQ(ar.size(), 6u);
}

TEST(Utility, DualArrayOutOfBound) {
  common::dual_array<int> ar(2, 3);
  ASSERT_DEATH({ ar(2, 0); }, ".");
  ASSERT_DEATH({ ar(-1, 0); }, ".");
  ASSERT_DEATH({ ar(0, 4); }, ".");
  ASSERT_DEATH({ ar(0, -1); }, ".");
}

TEST(Utility, PriorityQueue) {
  common::priority_queue<int> queue;
  for (auto v : {1, 3, 2, 4}) {
    queue.emplace(v);
  }
  {
    auto v = queue.top();
    queue.pop();
    ASSERT_EQ(v, 1);
  }
  {
    auto v = queue.top();
    queue.pop();
    ASSERT_EQ(v, 2);
  }
  {
    auto v = queue.top();
    queue.pop();
    ASSERT_EQ(v, 3);
  }
  {
    auto v = queue.top();
    queue.pop();
    ASSERT_EQ(v, 4);
  }
}
