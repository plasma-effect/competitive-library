#include "competitive/container/dual_array.hpp"
#include "competitive/stdio.hpp"
#include <gtest/gtest.h>

TEST(Container, DualArrayAssignAndRead) {
  competitive::dual_array<int> ar(2, 3);
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

TEST(Container, DualArrayAssignAndReadByAt) {
  competitive::dual_array<int> ar(2, 3);
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

TEST(Container, DualArrayGetDimensions) {
  competitive::dual_array<int> ar(2, 3);
  auto [d0, d1] = ar.dimensions();
  ASSERT_EQ(d0, 2u);
  ASSERT_EQ(d1, 3u);
}

TEST(Container, DualArrayGetSize) {
  competitive::dual_array<int> ar(2, 3);
  ASSERT_EQ(ar.size(), 6u);
}

TEST(Container, DualArrayOutOfBound) {
  competitive::dual_array<int> ar(2, 3);
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

TEST(Container, DualArrayBoolAssignAndRead) {
  competitive::dual_array<bool> ar(2, 2);
  ar(0, 0) = true;
  ar(1, 1) = true;
  ASSERT_EQ(ar(0, 0), true);
  ASSERT_EQ(ar(0, 1), false);
  ASSERT_EQ(ar(1, 0), false);
  ASSERT_EQ(ar(1, 1), true);
}

TEST(Container, DualArrayBoolAssignAndReadByAt) {
  competitive::dual_array<bool> ar(2, 2);
  ar.at(0, 0) = true;
  ar.at(1, 1) = true;
  ASSERT_EQ(ar.at(0, 0), true);
  ASSERT_EQ(ar.at(0, 1), false);
  ASSERT_EQ(ar.at(1, 0), false);
  ASSERT_EQ(ar.at(1, 1), true);
}

TEST(Container, DualArrayBoolGetDimensions) {
  competitive::dual_array<bool> ar(2, 3);
  auto [d0, d1] = ar.dimensions();
  ASSERT_EQ(d0, 2u);
  ASSERT_EQ(d1, 3u);
}

TEST(Container, DualArrayBoolGetSize) {
  competitive::dual_array<bool> ar(2, 3);
  ASSERT_EQ(ar.size(), 6u);
}

TEST(Container, DualArrayBoolOutOfBound) {
  competitive::dual_array<bool> ar(2, 3);
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

TEST(Container, DualArrayNormalPrint) {
  competitive::dual_array<int> ar(2, 3);
  ar(0, 0) = 1;
  ar(0, 1) = 2;
  ar(0, 2) = 3;
  ar(1, 0) = 4;
  ar(1, 1) = 5;
  ar(1, 2) = 6;
  testing::internal::CaptureStdout();
  competitive::println(ar);
  std::cout << std::flush;
  EXPECT_EQ(testing::internal::GetCapturedStdout(), "1 2 3 4 5 6\n");
}

TEST(Container, DualArrayBoolNormalPrint) {
  competitive::dual_array<bool> ar(2, 3);
  ar(0, 0) = true;
  ar(0, 1) = false;
  ar(0, 2) = true;
  ar(1, 0) = false;
  ar(1, 1) = true;
  ar(1, 2) = false;
  testing::internal::CaptureStdout();
  competitive::println(ar);
  std::cout << std::flush;
  EXPECT_EQ(testing::internal::GetCapturedStdout(), "1 0 1 0 1 0\n");
}

TEST(Container, DualArrayBoolElemNormalPrint) {
  competitive::dual_array<bool> ar(2, 2);
  ar(0, 0) = true;
  ar(0, 1) = false;
  ar(1, 0) = false;
  ar(1, 1) = true;
  testing::internal::CaptureStdout();
  competitive::println(ar(0, 0), ar(0, 1), ar(1, 0), ar(1, 1));
  std::cout << std::flush;
  EXPECT_EQ(testing::internal::GetCapturedStdout(), "1 0 0 1\n");
}

TEST(Container, DualArrayDebugPrint) {
  competitive::dual_array<int> ar(2, 3);
  ar(0, 0) = 1;
  ar(0, 1) = 2;
  ar(0, 2) = 3;
  ar(1, 0) = 4;
  ar(1, 1) = 5;
  ar(1, 2) = 6;
  testing::internal::CaptureStderr();
  competitive::debug::println(ar);
  EXPECT_EQ(testing::internal::GetCapturedStderr(), "{{1, 2, 3}, {4, 5, 6}}\n");
}

TEST(Container, DualArrayBoolDebugPrint) {
  competitive::dual_array<bool> ar(2, 3);
  ar(0, 0) = true;
  ar(0, 1) = false;
  ar(0, 2) = true;
  ar(1, 0) = false;
  ar(1, 1) = true;
  ar(1, 2) = false;
  testing::internal::CaptureStderr();
  competitive::debug::println(ar);
  EXPECT_EQ(testing::internal::GetCapturedStderr(), "{{1, 0, 1}, {0, 1, 0}}\n");
}

TEST(Container, DualArrayBoolElemDebugPrint) {
  competitive::dual_array<bool> ar(2, 2);
  ar(0, 0) = true;
  ar(0, 1) = false;
  ar(1, 0) = false;
  ar(1, 1) = true;
  testing::internal::CaptureStderr();
  competitive::debug::println(ar(0, 0), ar(0, 1), ar(1, 0), ar(1, 1));
  EXPECT_EQ(testing::internal::GetCapturedStderr(), "1 0 0 1\n");
}
