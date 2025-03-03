#include "heuristic.hpp"
#include <gtest/gtest-spi.h>
#include <gtest/gtest.h>
using namespace std::chrono_literals;

namespace {
template <typename Func> auto test_async(Func func) {
  return std::async(std::launch::async, func).get();
}
} // namespace

TEST(HeuristicGeneral, GetTime) {
  auto [first, second] = test_async([] {
    auto f = heuristic::get_time();
    std::this_thread::sleep_for(10ms);
    auto s = heuristic::get_time();
    return std::pair(f, s);
  });
  EXPECT_GE(first, 0ms);
  EXPECT_GT(second, first);
}

TEST(HeuristicGeneral, GetTimeThreadLocal) {
  auto f = test_async([] {
    heuristic::get_time();
    std::this_thread::sleep_for(10ms);
    return heuristic::get_time();
  });
  auto s = test_async([] { return heuristic::get_time(); });
  EXPECT_LT(s, f);
}

TEST(HeuristicGeneral, MakeUniformIntDistribution) {
  auto results = test_async([] {
    auto dist = heuristic::make_uniform_int_distribution(0, 3);
    std::array<int, 5> result{};
    for ([[maybe_unused]] auto _ : common::irange(10000)) {
      auto v = dist();
      if (v < 0 || v >= 4) {
        ++result[4];
      } else {
        ++result[v];
      }
    }
    return result;
  });
  EXPECT_NE(results[0], 0);
  EXPECT_NE(results[1], 0);
  EXPECT_NE(results[2], 0);
  EXPECT_NE(results[3], 0);
  EXPECT_EQ(results[4], 0);
}

TEST(HeuristicGeneral, GenerateCanonical) {
  EXPECT_TRUE(test_async([] {
    for ([[maybe_unused]] auto _ : common::irange(10000)) {
      auto v = heuristic::generate_canonical();
      if (v < 0.0 || v >= 1.0) {
        return false;
      }
    }
    return true;
  }));
}

TEST(HeuristicGeneral, GenerateCanonicalThreadLocal) {
  constexpr int N = 0x100;
  auto first = test_async([] {
    std::array<double, N> result{};
    for (auto& v : result) {
      v = heuristic::generate_canonical();
    }
    return result;
  });
  auto second = test_async([] {
    std::array<double, N> result{};
    for (auto& v : result) {
      v = heuristic::generate_canonical();
    }
    return result;
  });
  EXPECT_EQ(first, second);
}

TEST(HeuristicGeneral, ShuffleRng) {
  std::array<int, 8> base = {0, 1, 2, 3, 4, 5, 6, 7};
  auto [first, second] = test_async([base] {
    auto first_rng = base;
    heuristic::shuffle(first_rng);
    auto second_rng = base;
    heuristic::shuffle(second_rng);
    return std::pair(first_rng, second_rng);
  });
  for (auto i : common::irange(8)) {
    EXPECT_EQ(std::ranges::count(first, i), 1);
    EXPECT_EQ(std::ranges::count(second, i), 1);
  }
  EXPECT_NE(base, first);
  EXPECT_NE(base, second);
  EXPECT_NE(first, second);
}

TEST(HeuristicGeneral, ShuffleIterator) {
  std::array<int, 8> base = {0, 1, 2, 3, 4, 5, 6, 7};
  auto [first, second] = test_async([base] {
    auto first_rng = base;
    heuristic::shuffle(first_rng.begin(), first_rng.end());
    auto second_rng = base;
    heuristic::shuffle(second_rng.begin(), second_rng.end());
    return std::pair(first_rng, second_rng);
  });
  for (auto i : common::irange(8)) {
    EXPECT_EQ(std::ranges::count(first, i), 1);
    EXPECT_EQ(std::ranges::count(second, i), 1);
  }
  EXPECT_NE(base, first);
  EXPECT_NE(base, second);
  EXPECT_NE(first, second);
}

TEST(TimeControl, OperatorBool) {
  auto [first, second] = test_async([] {
    heuristic::time_control_t control(100ms);
    auto f = static_cast<bool>(control);
    std::this_thread::sleep_for(100ms);
    auto s = static_cast<bool>(control);
    return std::pair(f, s);
  });
  EXPECT_TRUE(first);
  EXPECT_FALSE(second);
}

TEST(TimeControl, Frequency) {
  auto result = test_async([] {
    std::array<bool, 4> ret{};
    heuristic::time_control_t control(100ms, 2);
    ret[0] = static_cast<bool>(control);
    ret[1] = static_cast<bool>(control);
    std::this_thread::sleep_for(100ms);
    ret[2] = static_cast<bool>(control);
    ret[3] = static_cast<bool>(control);
    return ret;
  });
  EXPECT_TRUE(result[0]);
  EXPECT_TRUE(result[1]);
  EXPECT_TRUE(result[2]);
  EXPECT_FALSE(result[3]);
}

TEST(TimeControl, AnnealingThreshold) {
  auto result = test_async([] {
    heuristic::time_control_t control(100ms);
    if (control.annealing_threshold(0.5) <= 1.0) {
      return false;
    } else if (control.annealing_threshold(0.0) != 1.0) {
      return false;
    } else if (control.annealing_threshold(-0.5) >= 1.0) {
      return false;
    }
    return true;
  });
  EXPECT_TRUE(result);
}

TEST(TimeControl, TransitionCheck) {
  auto result = test_async([] {
    heuristic::time_control_t control(100ms);
    std::array<int, 3> count{};
    count[0] = control.transition_check(1.0);
    for ([[maybe_unused]] auto _ : common::irange(10000)) {
      if (control.transition_check(-1000)) {
        ++count[1];
      } else {
        ++count[2];
      }
    }
    return count;
  });
  EXPECT_EQ(result[0], 1);
  EXPECT_NE(result[1], 0);
  EXPECT_NE(result[2], 0);
}

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

TEST(GridBFSQueue, General) {
  heuristic::grid_bfs_queue<int, 3, 3> queue;
  queue.emplace(0, 0, 0);
  common::dual_array<std::optional<int>> result(3, 3);
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
  common::dual_array<bool> maze(3, 5);
  maze(0, 1) = true;
  maze(1, 1) = true;
  maze(1, 3) = true;
  maze(2, 3) = true;
  heuristic::grid_bfs_queue<int, 3, 5> queue;
  queue.emplace(0, 0, 0);
  common::dual_array<std::optional<int>> result(3, 5);
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
  common::dual_array<bool> maze(3, 5);
  maze(0, 1) = true;
  maze(1, 1) = true;
  maze(1, 3) = true;
  maze(2, 3) = true;
  heuristic::grid_bfs_queue<common::pair<int>, 3, 5> queue;
  queue.emplace(0, 0, 0, 0);
  common::dual_array<common::pair<int>> result(3, 5);
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
  common::dual_array<int> count(3, 3);
  heuristic::grid_bfs_queue<int, 3, 3> queue;
  queue.emplace(0, 0);
  while (auto center = queue.pop()) {
    auto [ci, cj, _] = *center;
    heuristic::grid_bfs_queue<int, 3, 3> internal;
    for (auto i : common::irange(-1, 2)) {
      for (auto j : common::irange(-1, 2)) {
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
