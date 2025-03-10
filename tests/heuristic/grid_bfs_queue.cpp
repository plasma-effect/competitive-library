#include "heuristic/grid_bfs_queue.hpp"
#include "test_async.hpp"
#include <gtest/gtest.h>

TEST(GridBFSQueue, General) {
  heuristic::grid_bfs_queue<int, 3, 3> queue;
  queue.emplace(0, 0, 0);
  heuristic::static_dual_array<std::optional<int>, 3, 3> result;
  while (auto top = queue.pop()) {
    auto [i, j, d] = *top;
    EXPECT_FALSE(result(i, j)) << std::format("(i, j) = ({}, {})", i, j);
    result(i, j) = d;
    queue.push(i + 1, j, d + 1);
    queue.push(i, j + 1, d + 1);
    queue.push(i - 1, j, d + 1);
    queue.push(i, j + 1, d + 1);
  }
  EXPECT_EQ(result(0, 0), 0);
  EXPECT_EQ(result(0, 1), 1);
  EXPECT_EQ(result(0, 2), 2);
  EXPECT_EQ(result(1, 0), 1);
  EXPECT_EQ(result(1, 1), 2);
  EXPECT_EQ(result(1, 2), 3);
  EXPECT_EQ(result(2, 0), 2);
  EXPECT_EQ(result(2, 1), 3);
  EXPECT_EQ(result(2, 2), 4);
}

TEST(GridBFSQueue, Snake) {
  // .#...
  // .#.#.
  // ...#.
  heuristic::static_dual_array<bool, 3, 5> maze;
  maze(0, 1) = true;
  maze(1, 1) = true;
  maze(1, 3) = true;
  maze(2, 3) = true;
  heuristic::grid_bfs_queue<int, 3, 5> queue;
  queue.emplace(0, 0, 0);
  heuristic::static_dual_array<std::optional<int>, 3, 5> result;
  while (auto top = queue.pop()) {
    auto [i, j, d] = *top;
    EXPECT_FALSE(result(i, j)) << std::format("(i, j) = ({}, {})", i, j);
    if (maze(i, j)) {
      continue;
    }
    result(i, j) = d;
    queue.push(i + 1, j, d + 1);
    queue.push(i, j + 1, d + 1);
    queue.push(i - 1, j, d + 1);
    queue.push(i, j + 1, d + 1);
  }
  EXPECT_EQ(result(0, 0), 0);
  EXPECT_EQ(result(0, 1), std::nullopt);
  EXPECT_EQ(result(0, 2), 6);
  EXPECT_EQ(result(0, 3), 7);
  EXPECT_EQ(result(0, 4), 8);
  EXPECT_EQ(result(1, 0), 1);
  EXPECT_EQ(result(1, 1), std::nullopt);
  EXPECT_EQ(result(1, 2), 5);
  EXPECT_EQ(result(1, 3), std::nullopt);
  EXPECT_EQ(result(1, 4), 9);
  EXPECT_EQ(result(2, 0), 2);
  EXPECT_EQ(result(2, 1), 3);
  EXPECT_EQ(result(2, 2), 4);
  EXPECT_EQ(result(2, 3), std::nullopt);
  EXPECT_EQ(result(2, 4), 10);
}

TEST(GridBFSQueue, Emplace) {
  // .#...
  // .#.#.
  // ...#.
  heuristic::static_dual_array<bool, 3, 5> maze;
  maze(0, 1) = true;
  maze(1, 1) = true;
  maze(1, 3) = true;
  maze(2, 3) = true;
  heuristic::grid_bfs_queue<std::pair<int, int>, 3, 5> queue;
  queue.emplace(0, 0, 0, 0);
  heuristic::static_dual_array<std::pair<int, int>, 3, 5> result;
  while (auto top = queue.pop()) {
    auto [i, j, p] = *top;
    if (maze(i, j)) {
      continue;
    }
    result(i, j) = p;
    queue.emplace(i + 1, j, i, j);
    queue.emplace(i, j + 1, i, j);
    queue.emplace(i - 1, j, i, j);
    queue.emplace(i, j - 1, i, j);
  }
  EXPECT_EQ(result(0, 0), std::pair(0, 0));
  EXPECT_EQ(result(1, 0), std::pair(0, 0));
  EXPECT_EQ(result(2, 0), std::pair(1, 0));
  EXPECT_EQ(result(2, 1), std::pair(2, 0));
  EXPECT_EQ(result(2, 2), std::pair(2, 1));
  EXPECT_EQ(result(1, 2), std::pair(2, 2));
  EXPECT_EQ(result(0, 2), std::pair(1, 2));
  EXPECT_EQ(result(0, 3), std::pair(0, 2));
  EXPECT_EQ(result(0, 4), std::pair(0, 3));
  EXPECT_EQ(result(1, 4), std::pair(0, 4));
  EXPECT_EQ(result(2, 4), std::pair(1, 4));
}

TEST(GridBFSQueue, Recursive) {
  heuristic::static_dual_array<int, 3, 3> count;
  heuristic::grid_bfs_queue<int, 3, 3> queue;
  queue.emplace(0, 0);
  while (auto center = queue.pop()) {
    auto [ci, cj, _] = *center;
    heuristic::grid_bfs_queue<int, 3, 3> internal;
    for (int i = -1; i <= 1; ++i) {
      for (int j = -1; j <= 1; ++j) {
        internal.emplace(ci + i, cj + j);
      }
    }
    while (auto p = internal.pop()) {
      auto [i, j, _2] = *p;
      ++count(i, j);
    }
    queue.emplace(ci + 1, cj);
    queue.emplace(ci, cj + 1);
  }
  EXPECT_EQ(count(0, 0), 4);
  EXPECT_EQ(count(0, 1), 6);
  EXPECT_EQ(count(0, 2), 4);
  EXPECT_EQ(count(1, 0), 6);
  EXPECT_EQ(count(1, 1), 9);
  EXPECT_EQ(count(1, 2), 6);
  EXPECT_EQ(count(2, 0), 4);
  EXPECT_EQ(count(2, 1), 6);
  EXPECT_EQ(count(2, 2), 4);
}
