#include "competitive/io/normal_print.hpp"
#include <gtest/gtest.h>
using testing::internal::CaptureStdout;
using testing::internal::GetCapturedStdout;

TEST(NormalPrint, Integer1) {
  CaptureStdout();
  common::println(1);
  std::cout << std::flush;
  EXPECT_EQ(GetCapturedStdout(), "1\n");
}

TEST(NormalPrint, Integer2) {
  CaptureStdout();
  common::println(1, 2);
  std::cout << std::flush;
  EXPECT_EQ(GetCapturedStdout(), "1 2\n");
}

TEST(NormalPrint, IntVector) {
  CaptureStdout();
  std::vector vec = {1, 2, 3};
  common::println(vec);
  std::cout << std::flush;
  EXPECT_EQ(GetCapturedStdout(), "1 2 3\n");
}

TEST(NormalPrint, Irange) {
  CaptureStdout();
  common::println(common::irange(5));
  std::cout << std::flush;
  EXPECT_EQ(GetCapturedStdout(), "0 1 2 3 4\n");
}

TEST(NormalPrint, Pair) {
  CaptureStdout();
  common::println(std::make_pair(1, 2.5));
  std::cout << std::flush;
  EXPECT_EQ(GetCapturedStdout(), "1 2.5\n");
}

TEST(NormalPrint, Tuple) {
  CaptureStdout();
  common::println(std::make_tuple(1, 2.5, "3"));
  std::cout << std::flush;
  EXPECT_EQ(GetCapturedStdout(), "1 2.5 3\n");
}

TEST(NormalPrint, TupleVector) {
  CaptureStdout();
  std::vector vec = {
      std::make_tuple(1, 2, 3),
      std::make_tuple(4, 5, 6),
  };
  common::println(vec);
  std::cout << std::flush;
  EXPECT_EQ(GetCapturedStdout(), "1 2 3 4 5 6\n");
}

TEST(NormalPrint, UseManip) {
  CaptureStdout();
  common::println(std::boolalpha, true);
  std::cout << std::flush;
  EXPECT_EQ(GetCapturedStdout(), "true\n");
}

TEST(NormalPrint, DualArray) {
  CaptureStdout();
  common::dual_array<int> ar(2, 3);
  ar(0, 0) = 1;
  ar(0, 1) = 2;
  ar(0, 2) = 3;
  ar(1, 0) = 4;
  ar(1, 1) = 5;
  ar(1, 2) = 6;
  common::println(ar);
  std::cout << std::flush;
  EXPECT_EQ(GetCapturedStdout(), "1 2 3 4 5 6\n");
}

TEST(NormalPrint, BooleanDualArray) {
  CaptureStdout();
  common::dual_array<bool> ar(2, 3);
  ar(0, 0) = true;
  ar(0, 1) = false;
  ar(0, 2) = true;
  ar(1, 0) = false;
  ar(1, 1) = true;
  ar(1, 2) = false;
  common::println(ar);
  std::cout << std::flush;
  EXPECT_EQ(GetCapturedStdout(), "1 0 1 0 1 0\n");
}
