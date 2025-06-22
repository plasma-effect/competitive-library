#include "utility/irange.hpp"
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
