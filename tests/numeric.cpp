#include "numeric.hpp"
#include <gtest/gtest.h>

TEST(Numeric, MonoidPlus) {
  constexpr auto plus = numeric::plus<int>;
  EXPECT_EQ(plus(0b0101'0101'0101'0101, 0b1010'1010'1010'1010), 0xFFFF);
  EXPECT_EQ(plus(1, plus(2, 3)), 6);
  EXPECT_EQ(plus(), 0);
}

TEST(Numeric, MonoidMultiplies) {
  constexpr auto multiplies = numeric::multiplies<int>;
  EXPECT_EQ(multiplies(0b100, 0b1000), 0b100000);
  EXPECT_EQ(multiplies(2, multiplies(3, 4)), 24);
  EXPECT_EQ(multiplies(), 1);
}

TEST(Numeric, MonoidMin) {
  constexpr auto min = numeric::min<int>;
  EXPECT_EQ(min(10, 5), 5);
  EXPECT_EQ(min(10, min(5, 12)), 5);
  EXPECT_EQ(min(), INT_MAX);
}

TEST(Numeric, MonoidMax) {
  constexpr auto max = numeric::max<int>;
  EXPECT_EQ(max(10, 5), 10);
  EXPECT_EQ(max(10, max(5, 12)), 12);
  EXPECT_EQ(max(), INT_MIN);
}
