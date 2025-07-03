#include "competitive/heuristic/static_container.hpp"
#include "competitive/stdio.hpp"
#include <gtest/gtest.h>

TEST(StaticPriorityContainer, General) {
  heuristic::static_priority_container<int, 4> container;
  container.push(0);
  EXPECT_EQ(container.size(), 1);
  container.push(1);
  EXPECT_EQ(container.size(), 2);
  container.push(2);
  EXPECT_EQ(container.size(), 3);
  container.push(3);
  EXPECT_EQ(container.size(), 4);
  EXPECT_EQ(std::ranges::count(container, 0), 1);
  EXPECT_EQ(std::ranges::count(container, 1), 1);
  EXPECT_EQ(std::ranges::count(container, 2), 1);
  EXPECT_EQ(std::ranges::count(container, 3), 1);

  container.push(4);
  EXPECT_EQ(container.size(), 4);
  EXPECT_EQ(std::ranges::count(container, 0), 0);
  EXPECT_EQ(std::ranges::count(container, 1), 1);
  EXPECT_EQ(std::ranges::count(container, 2), 1);
  EXPECT_EQ(std::ranges::count(container, 3), 1);
  EXPECT_EQ(std::ranges::count(container, 4), 1);

  container.push(-1);
  EXPECT_EQ(container.size(), 4);
  EXPECT_EQ(std::ranges::count(container, -1), 0);
  EXPECT_EQ(std::ranges::count(container, 0), 0);
  EXPECT_EQ(std::ranges::count(container, 1), 1);
  EXPECT_EQ(std::ranges::count(container, 2), 1);
  EXPECT_EQ(std::ranges::count(container, 3), 1);
  EXPECT_EQ(std::ranges::count(container, 4), 1);

  container.clear();
  EXPECT_EQ(container.size(), 0);
}

TEST(StaticPriorityContainer, Less) {
  heuristic::static_priority_container<int, 4, common::priority::less>
      container;
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

TEST(StaticPriorityContainer, Greater) {
  heuristic::static_priority_container<int, 4, common::priority::greater>
      container;
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

TEST(StaticPriorityContainer, WithProj) {
  heuristic::static_priority_container<std::pair<int, int>, 4> container(
      [](auto p) { return std::get<0>(p) + std::get<1>(p); });
  container.emplace(3, 0);
  container.emplace(2, 2);
  container.emplace(1, 4);
  container.emplace(0, 6);
  EXPECT_EQ(std::ranges::count(container, std::pair(3, 0)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(2, 2)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(1, 4)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(0, 6)), 1);

  container.emplace(-1, 8);
  EXPECT_EQ(std::ranges::count(container, std::pair(3, 0)), 0);
  EXPECT_EQ(std::ranges::count(container, std::pair(2, 2)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(1, 4)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(0, 6)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(-1, 8)), 1);

  container.emplace(4, -2);
  EXPECT_EQ(std::ranges::count(container, std::pair(3, 0)), 0);
  EXPECT_EQ(std::ranges::count(container, std::pair(3, 0)), 0);
  EXPECT_EQ(std::ranges::count(container, std::pair(2, 2)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(1, 4)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(0, 6)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(-1, 8)), 1);
}

TEST(StaticPriorityContainer, LessWithProj) {
  heuristic::static_priority_container<std::pair<int, int>, 4,
                                       common::priority::less>
      container([](auto p) { return std::get<0>(p) + std::get<1>(p); });
  container.emplace(3, 0);
  container.emplace(2, 2);
  container.emplace(1, 4);
  container.emplace(0, 6);
  EXPECT_EQ(std::ranges::count(container, std::pair(3, 0)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(2, 2)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(1, 4)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(0, 6)), 1);

  container.emplace(-1, 8);
  EXPECT_EQ(std::ranges::count(container, std::pair(3, 0)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(2, 2)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(1, 4)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(0, 6)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(-1, 8)), 0);

  container.emplace(4, -2);
  EXPECT_EQ(std::ranges::count(container, std::pair(3, 0)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(3, 0)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(2, 2)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(1, 4)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(0, 6)), 0);
  EXPECT_EQ(std::ranges::count(container, std::pair(-1, 8)), 0);
}

TEST(StaticPriorityContainer, GreaterWithProj) {
  heuristic::static_priority_container<std::pair<int, int>, 4,
                                       common::priority::greater>
      container([](auto p) { return std::get<0>(p) + std::get<1>(p); });
  container.emplace(3, 0);
  container.emplace(2, 2);
  container.emplace(1, 4);
  container.emplace(0, 6);
  EXPECT_EQ(std::ranges::count(container, std::pair(3, 0)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(2, 2)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(1, 4)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(0, 6)), 1);

  container.emplace(-1, 8);
  EXPECT_EQ(std::ranges::count(container, std::pair(3, 0)), 0);
  EXPECT_EQ(std::ranges::count(container, std::pair(2, 2)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(1, 4)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(0, 6)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(-1, 8)), 1);

  container.emplace(4, -2);
  EXPECT_EQ(std::ranges::count(container, std::pair(3, 0)), 0);
  EXPECT_EQ(std::ranges::count(container, std::pair(3, 0)), 0);
  EXPECT_EQ(std::ranges::count(container, std::pair(2, 2)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(1, 4)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(0, 6)), 1);
  EXPECT_EQ(std::ranges::count(container, std::pair(-1, 8)), 1);
}
