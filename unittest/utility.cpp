#include "utility.hpp"
#include <gtest/gtest.h>

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

TEST(Utility, DualArrayBoolAssignAndRead) {
  common::dual_array<bool> ar(2, 2);
  ar(0, 0) = true;
  ar(1, 1) = true;
  ASSERT_EQ(ar(0, 0), true);
  ASSERT_EQ(ar(0, 1), false);
  ASSERT_EQ(ar(1, 0), false);
  ASSERT_EQ(ar(1, 1), true);
}

TEST(Utility, DualArrayBoolGetDimensions) {
  common::dual_array<bool> ar(2, 3);
  auto [d0, d1] = ar.dimensions();
  ASSERT_EQ(d0, 2u);
  ASSERT_EQ(d1, 3u);
}

TEST(Utility, DualArrayBoolGetSize) {
  common::dual_array<bool> ar(2, 3);
  ASSERT_EQ(ar.size(), 6u);
}

#ifdef LOCAL_DEBUG
TEST(Utility, DualArrayOutOfBound) {
  common::dual_array<int> ar(2, 3);
  ASSERT_THROW({ ar(2, 0); }, std::logic_error);
  ASSERT_THROW({ ar(-1, 0); }, std::logic_error);
  ASSERT_THROW({ ar(0, 4); }, std::logic_error);
  ASSERT_THROW({ ar(0, -1); }, std::logic_error);

  const auto& car = ar;
  ASSERT_THROW({ car(2, 0); }, std::logic_error);
  ASSERT_THROW({ car(-1, 0); }, std::logic_error);
  ASSERT_THROW({ car(0, 4); }, std::logic_error);
  ASSERT_THROW({ car(0, -1); }, std::logic_error);
}

TEST(Utility, DualArrayBoolOutOfBound) {
  common::dual_array<bool> ar(2, 3);
  ASSERT_THROW({ ar(2, 0); }, std::logic_error);
  ASSERT_THROW({ ar(-1, 0); }, std::logic_error);
  ASSERT_THROW({ ar(0, 4); }, std::logic_error);
  ASSERT_THROW({ ar(0, -1); }, std::logic_error);

  const auto& car = ar;
  ASSERT_THROW({ car(2, 0); }, std::logic_error);
  ASSERT_THROW({ car(-1, 0); }, std::logic_error);
  ASSERT_THROW({ car(0, 4); }, std::logic_error);
  ASSERT_THROW({ car(0, -1); }, std::logic_error);
}
#endif

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

#ifdef LOCAL_DEBUG
static_assert(common::is_debug());
#else
static_assert(!common::is_debug());
#endif
