#include "competitive/container/static_stack.hpp"
#include <gtest/gtest.h>

TEST(StaticStack, General) {
  competitive::static_stack<int, 3> stack;
  stack.emplace(1);
  stack.emplace(2);
  EXPECT_EQ(stack.size(), 2);

  EXPECT_EQ(stack.pop(), 2);
  EXPECT_EQ(stack.size(), 1);

  stack.emplace(3);
  stack.emplace(4);
  EXPECT_EQ(stack.size(), 3);

  EXPECT_EQ(stack.pop(), 4);
  EXPECT_EQ(stack.size(), 2);
  EXPECT_EQ(stack.pop(), 3);
  EXPECT_EQ(stack.size(), 1);
  EXPECT_EQ(stack.pop(), 1);
  EXPECT_EQ(stack.size(), 0);
}
