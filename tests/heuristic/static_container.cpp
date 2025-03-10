#include "heuristic/static_container.hpp"
#include "test_async.hpp"
#include <gtest/gtest.h>

TEST(StaticPriorityContainer, General) {
  heuristic::static_priority_container<int, 4> container;
  container.push(0);
  container.push(1);
  container.push(2);
  container.push(3);
  EXPECT_EQ(std::ranges::count(container, 0), 1);
  EXPECT_EQ(std::ranges::count(container, 1), 1);
  EXPECT_EQ(std::ranges::count(container, 2), 1);
  EXPECT_EQ(std::ranges::count(container, 3), 1);

  container.push(4);
  EXPECT_EQ(std::ranges::count(container, 0), 0);
  EXPECT_EQ(std::ranges::count(container, 1), 1);
  EXPECT_EQ(std::ranges::count(container, 2), 1);
  EXPECT_EQ(std::ranges::count(container, 3), 1);
  EXPECT_EQ(std::ranges::count(container, 4), 1);

  container.push(-1);
  EXPECT_EQ(std::ranges::count(container, -1), 0);
  EXPECT_EQ(std::ranges::count(container, 0), 0);
  EXPECT_EQ(std::ranges::count(container, 1), 1);
  EXPECT_EQ(std::ranges::count(container, 2), 1);
  EXPECT_EQ(std::ranges::count(container, 3), 1);
  EXPECT_EQ(std::ranges::count(container, 4), 1);
}

TEST(StaticPriorityContainer, CustomCompare) {
  heuristic::static_priority_container<int, 4, std::less<>> container;
  container.push(0);
  container.push(1);
  container.push(2);
  container.push(3);
  EXPECT_EQ(std::ranges::count(container, 0), 1);
  EXPECT_EQ(std::ranges::count(container, 1), 1);
  EXPECT_EQ(std::ranges::count(container, 2), 1);
  EXPECT_EQ(std::ranges::count(container, 3), 1);

  container.push(4);
  EXPECT_EQ(std::ranges::count(container, 0), 1);
  EXPECT_EQ(std::ranges::count(container, 1), 1);
  EXPECT_EQ(std::ranges::count(container, 2), 1);
  EXPECT_EQ(std::ranges::count(container, 3), 1);
  EXPECT_EQ(std::ranges::count(container, 4), 0);

  container.push(-1);
  EXPECT_EQ(std::ranges::count(container, -1), 1);
  EXPECT_EQ(std::ranges::count(container, 0), 1);
  EXPECT_EQ(std::ranges::count(container, 1), 1);
  EXPECT_EQ(std::ranges::count(container, 2), 1);
  EXPECT_EQ(std::ranges::count(container, 3), 0);
  EXPECT_EQ(std::ranges::count(container, 4), 0);
}
