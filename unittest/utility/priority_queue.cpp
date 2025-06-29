#include "competitive/utility/priority_queue.hpp"
#include <gtest/gtest.h>

TEST(Utility, PriorityQueueDefault) {
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

TEST(Utility, PriorityQueueLess) {
  common::priority_queue<int, common::priority::less> queue;
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

TEST(Utility, PriorityQueueGreater) {
  common::priority_queue<int, common::priority::greater> queue;
  for (auto v : {1, 3, 2, 4}) {
    queue.emplace(v);
  }
  {
    auto v = queue.top();
    queue.pop();
    ASSERT_EQ(v, 4);
  }
  {
    auto v = queue.top();
    queue.pop();
    ASSERT_EQ(v, 3);
  }
  {
    auto v = queue.top();
    queue.pop();
    ASSERT_EQ(v, 2);
  }
  {
    auto v = queue.top();
    queue.pop();
    ASSERT_EQ(v, 1);
  }
}

TEST(Utility, PriorityQueueWithProjection) {
  common::priority_queue<std::pair<int, int>> queue(
      [](std::tuple<int, int> t) { return std::get<0>(t) + std::get<1>(t); });
  for (auto v :
       {std::pair(0, 1), std::pair(2, 1), std::pair(1, 1), std::pair(2, 2)}) {
    queue.emplace(v);
  }
  {
    auto [v0, v1] = queue.top();
    queue.pop();
    ASSERT_EQ(v0, 0);
    ASSERT_EQ(v1, 1);
  }
  {
    auto [v0, v1] = queue.top();
    queue.pop();
    ASSERT_EQ(v0, 1);
    ASSERT_EQ(v1, 1);
  }
  {
    auto [v0, v1] = queue.top();
    queue.pop();
    ASSERT_EQ(v0, 2);
    ASSERT_EQ(v1, 1);
  }
  {
    auto [v0, v1] = queue.top();
    queue.pop();
    ASSERT_EQ(v0, 2);
    ASSERT_EQ(v1, 2);
  }
}

TEST(Utility, PriorityQueueLessWithProj) {
  common::priority_queue<std::pair<int, int>, common::priority::less> queue(
      [](std::tuple<int, int> t) { return std::get<0>(t) + std::get<1>(t); });
  for (auto v :
       {std::pair(0, 1), std::pair(2, 1), std::pair(1, 1), std::pair(2, 2)}) {
    queue.emplace(v);
  }
  {
    auto [v0, v1] = queue.top();
    queue.pop();
    ASSERT_EQ(v0, 0);
    ASSERT_EQ(v1, 1);
  }
  {
    auto [v0, v1] = queue.top();
    queue.pop();
    ASSERT_EQ(v0, 1);
    ASSERT_EQ(v1, 1);
  }
  {
    auto [v0, v1] = queue.top();
    queue.pop();
    ASSERT_EQ(v0, 2);
    ASSERT_EQ(v1, 1);
  }
  {
    auto [v0, v1] = queue.top();
    queue.pop();
    ASSERT_EQ(v0, 2);
    ASSERT_EQ(v1, 2);
  }
}

TEST(Utility, PriorityQueueGreaterWithProj) {
  common::priority_queue<std::pair<int, int>, common::priority::greater> queue(
      [](std::tuple<int, int> t) { return std::get<0>(t) + std::get<1>(t); });
  for (auto v :
       {std::pair(0, 1), std::pair(2, 1), std::pair(1, 1), std::pair(2, 2)}) {
    queue.emplace(v);
  }
  {
    auto [v0, v1] = queue.top();
    queue.pop();
    ASSERT_EQ(v0, 2);
    ASSERT_EQ(v1, 2);
  }
  {
    auto [v0, v1] = queue.top();
    queue.pop();
    ASSERT_EQ(v0, 2);
    ASSERT_EQ(v1, 1);
  }
  {
    auto [v0, v1] = queue.top();
    queue.pop();
    ASSERT_EQ(v0, 1);
    ASSERT_EQ(v1, 1);
  }
  {
    auto [v0, v1] = queue.top();
    queue.pop();
    ASSERT_EQ(v0, 0);
    ASSERT_EQ(v1, 1);
  }
}
