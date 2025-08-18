#include "competitive/container/static_queue.hpp"
#include <gtest/gtest.h>

TEST(StaticQueue, General) {
  competitive::static_queue<int, 3> queue;
  queue.emplace(1);
  queue.emplace(2);
  EXPECT_EQ(queue.size(), 2);

  EXPECT_EQ(queue.pop(), 1);
  EXPECT_EQ(queue.size(), 1);

  queue.emplace(3);
  queue.emplace(4);
  EXPECT_EQ(queue.size(), 3);

  EXPECT_EQ(queue.pop(), 2);
  EXPECT_EQ(queue.size(), 2);
  EXPECT_EQ(queue.pop(), 3);
  EXPECT_EQ(queue.size(), 1);
  EXPECT_EQ(queue.pop(), 4);
  EXPECT_EQ(queue.size(), 0);
}
