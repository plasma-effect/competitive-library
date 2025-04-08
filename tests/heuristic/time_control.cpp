#include "heuristic/time_control.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>
using namespace std::chrono_literals;

TEST(HeuristicGeneral, GetTime) {
  auto [first, second] = test_utils::async([] {
    auto f = heuristic::get_time();
    std::this_thread::sleep_for(10ms);
    auto s = heuristic::get_time();
    return std::pair(f, s);
  });
  EXPECT_GE(first, 0ms);
  EXPECT_GT(second, first);
}

TEST(HeuristicGeneral, GetTimeThreadLocal) {
  auto f = test_utils::async([] {
    heuristic::get_time();
    std::this_thread::sleep_for(10ms);
    return heuristic::get_time();
  });
  auto s = test_utils::async([] { return heuristic::get_time(); });
  EXPECT_LT(s, f);
}

TEST(TimeControl, OperatorBool) {
  auto [first, second] = test_utils::async([] {
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
  auto result = test_utils::async([] {
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
  auto result = test_utils::async([] {
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
  auto result = test_utils::async([] {
    heuristic::time_control_t control(100ms);
    std::array<int, 3> count{};
    count[0] = control.transition_check(1.0);
    for (int c = 0; c < 10000; ++c) {
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
