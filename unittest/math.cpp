#include "math.hpp"
#include <gtest/gtest.h>

TEST(Math, Abs) {
  static_assert(
      std::is_same_v<decltype(common::abs(std::declval<int>())), int>);
  static_assert(
      std::is_same_v<decltype(common::abs(std::declval<std::int64_t>())),
                     std::int64_t>);
  static_assert(
      std::is_same_v<decltype(common::abs(std::declval<std::uint64_t>())),
                     std::uint64_t>);
  static_assert(
      std::is_same_v<decltype(common::abs(std::declval<std::size_t>())),
                     std::size_t>);
  EXPECT_EQ(common::abs(1), 1);
  EXPECT_EQ(common::abs(3), 3);
  EXPECT_EQ(common::abs(-1), 1);
  EXPECT_EQ(common::abs(-3), 3);
  EXPECT_EQ(common::abs(0), 0);

  EXPECT_EQ(common::abs(0u), 0u);
  EXPECT_EQ(common::abs(1u), 1u);
  EXPECT_EQ(common::abs(3u), 3u);
}
