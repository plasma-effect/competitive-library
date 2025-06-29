#include "heuristic/static_container.hpp"
#include "debug_print.hpp"
#include "normal_print.hpp"
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

TEST(StaticDualArray, DualArrayAssignAndRead) {
  heuristic::static_dual_array<int, 2, 3> ar;
  ar(0, 0) = 0;
  ar(0, 1) = 1;
  ar(0, 2) = 2;
  ar(1, 0) = 3;
  ar(1, 1) = 4;
  ar(1, 2) = 5;
  ASSERT_EQ(ar(0, 0), 0);
  ASSERT_EQ(ar(0, 1), 1);
  ASSERT_EQ(ar(0, 2), 2);
  ASSERT_EQ(ar(1, 0), 3);
  ASSERT_EQ(ar(1, 1), 4);
  ASSERT_EQ(ar(1, 2), 5);
}

TEST(StaticDualArray, DualArrayAssignAndReadByAt) {
  heuristic::static_dual_array<int, 2, 3> ar;
  ar.at(0, 0) = 0;
  ar.at(0, 1) = 1;
  ar.at(0, 2) = 2;
  ar.at(1, 0) = 3;
  ar.at(1, 1) = 4;
  ar.at(1, 2) = 5;
  ASSERT_EQ(ar.at(0, 0), 0);
  ASSERT_EQ(ar.at(0, 1), 1);
  ASSERT_EQ(ar.at(0, 2), 2);
  ASSERT_EQ(ar.at(1, 0), 3);
  ASSERT_EQ(ar.at(1, 1), 4);
  ASSERT_EQ(ar.at(1, 2), 5);
}

TEST(StaticDualArray, DualArrayGetDimensions) {
  heuristic::static_dual_array<int, 2, 3> ar;
  auto [d0, d1] = ar.dimensions();
  ASSERT_EQ(d0, 2u);
  ASSERT_EQ(d1, 3u);
}

TEST(StaticDualArray, DualArrayGetSize) {
  heuristic::static_dual_array<int, 2, 3> ar;
  ASSERT_EQ(ar.size(), 6u);
}

TEST(StaticDualArray, DualArrayOutOfBound) {
  heuristic::static_dual_array<int, 2, 3> ar;
  const auto& car = ar;

#ifdef LOCAL_DEBUG
  ASSERT_THROW({ ar(2, 4); }, std::logic_error);
  ASSERT_THROW({ ar(2, 0); }, std::logic_error);
  ASSERT_THROW({ ar(2, -1); }, std::logic_error);
  ASSERT_THROW({ ar(0, 4); }, std::logic_error);
  ASSERT_THROW({ ar(0, -1); }, std::logic_error);
  ASSERT_THROW({ ar(-1, 4); }, std::logic_error);
  ASSERT_THROW({ ar(-1, 0); }, std::logic_error);
  ASSERT_THROW({ ar(-1, -1); }, std::logic_error);

  ASSERT_THROW({ car(2, 4); }, std::logic_error);
  ASSERT_THROW({ car(2, 0); }, std::logic_error);
  ASSERT_THROW({ car(2, -1); }, std::logic_error);
  ASSERT_THROW({ car(0, 4); }, std::logic_error);
  ASSERT_THROW({ car(0, -1); }, std::logic_error);
  ASSERT_THROW({ car(-1, 4); }, std::logic_error);
  ASSERT_THROW({ car(-1, 0); }, std::logic_error);
  ASSERT_THROW({ car(-1, -1); }, std::logic_error);
#else
  ASSERT_DEATH({ ar(2, 4); }, ".");
  ASSERT_DEATH({ ar(2, 0); }, ".");
  ASSERT_DEATH({ ar(2, -1); }, ".");
  ASSERT_DEATH({ ar(0, 4); }, ".");
  ASSERT_DEATH({ ar(0, -1); }, ".");
  ASSERT_DEATH({ ar(-1, 4); }, ".");
  ASSERT_DEATH({ ar(-1, 0); }, ".");
  ASSERT_DEATH({ ar(-1, -1); }, ".");

  ASSERT_DEATH({ car(2, 4); }, ".");
  ASSERT_DEATH({ car(2, 0); }, ".");
  ASSERT_DEATH({ car(2, -1); }, ".");
  ASSERT_DEATH({ car(0, 4); }, ".");
  ASSERT_DEATH({ car(0, -1); }, ".");
  ASSERT_DEATH({ car(-1, 4); }, ".");
  ASSERT_DEATH({ car(-1, 0); }, ".");
  ASSERT_DEATH({ car(-1, -1); }, ".");
#endif
  ASSERT_THROW({ ar.at(2, 4); }, std::out_of_range);
  ASSERT_THROW({ ar.at(2, 0); }, std::out_of_range);
  ASSERT_THROW({ ar.at(2, -1); }, std::out_of_range);
  ASSERT_THROW({ ar.at(0, 4); }, std::out_of_range);
  ASSERT_THROW({ ar.at(0, -1); }, std::out_of_range);
  ASSERT_THROW({ ar.at(-1, 4); }, std::out_of_range);
  ASSERT_THROW({ ar.at(-1, 0); }, std::out_of_range);
  ASSERT_THROW({ ar.at(-1, -1); }, std::out_of_range);

  ASSERT_THROW({ car.at(2, 4); }, std::out_of_range);
  ASSERT_THROW({ car.at(2, 0); }, std::out_of_range);
  ASSERT_THROW({ car.at(2, -1); }, std::out_of_range);
  ASSERT_THROW({ car.at(0, 4); }, std::out_of_range);
  ASSERT_THROW({ car.at(0, -1); }, std::out_of_range);
  ASSERT_THROW({ car.at(-1, 4); }, std::out_of_range);
  ASSERT_THROW({ car.at(-1, 0); }, std::out_of_range);
  ASSERT_THROW({ car.at(-1, -1); }, std::out_of_range);
}

TEST(StaticDualArray, DebugPrint) {
  heuristic::static_dual_array<int, 2, 3> ar;
  ar(0, 0) = 0;
  ar(0, 1) = 1;
  ar(0, 2) = 2;
  ar(1, 0) = 3;
  ar(1, 1) = 4;
  ar(1, 2) = 5;
  testing::internal::CaptureStderr();
  debug::println(ar);
  EXPECT_EQ(testing::internal::GetCapturedStderr(), "{{0, 1, 2}, {3, 4, 5}}\n");
}

TEST(StaticDualArray, NormalPrint) {
  heuristic::static_dual_array<int, 2, 3> ar;
  ar(0, 0) = 0;
  ar(0, 1) = 1;
  ar(0, 2) = 2;
  ar(1, 0) = 3;
  ar(1, 1) = 4;
  ar(1, 2) = 5;
  testing::internal::CaptureStdout();
  common::println(ar);
  EXPECT_EQ(testing::internal::GetCapturedStdout(), "0 1 2 3 4 5\n");
}
