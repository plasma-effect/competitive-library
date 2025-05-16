#include "math.hpp"
#include "atcoder/all"
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

TEST(Math, FactorialInt) {
  auto fact = common::make_factorial_array<int>(5);
  ASSERT_EQ(fact.size(), 6);
  EXPECT_EQ(fact[0], 1);
  EXPECT_EQ(fact[1], 1);
  EXPECT_EQ(fact[2], 2);
  EXPECT_EQ(fact[3], 6);
  EXPECT_EQ(fact[4], 24);
  EXPECT_EQ(fact[5], 120);
}

TEST(Math, FactorialModInt) {
  using modint = atcoder::static_modint<7>;
  auto fact = common::make_factorial_array<modint>(5);
  ASSERT_EQ(fact.size(), 6);
  EXPECT_EQ(fact[0], 1);
  EXPECT_EQ(fact[1], 1);
  EXPECT_EQ(fact[2], 2);
  EXPECT_EQ(fact[3], 6);
  EXPECT_EQ(fact[4], 3);
  EXPECT_EQ(fact[5], 1);
}
