#include "competitive/io/normal_print.hpp"
#include "competitive/utility/irange.hpp"
#include <gtest/gtest.h>
using testing::internal::CaptureStdout;
using testing::internal::GetCapturedStdout;

TEST(NormalPrint, Integer1) {
  CaptureStdout();
  competitive::println(1);
  std::cout << std::flush;
  EXPECT_EQ(GetCapturedStdout(), "1\n");
}

TEST(NormalPrint, Integer2) {
  CaptureStdout();
  competitive::println(1, 2);
  std::cout << std::flush;
  EXPECT_EQ(GetCapturedStdout(), "1 2\n");
}

TEST(NormalPrint, IntVector) {
  CaptureStdout();
  std::vector vec = {1, 2, 3};
  competitive::println(vec);
  std::cout << std::flush;
  EXPECT_EQ(GetCapturedStdout(), "1 2 3\n");
}

TEST(NormalPrint, Irange) {
  CaptureStdout();
  competitive::println(competitive::irange(5));
  std::cout << std::flush;
  EXPECT_EQ(GetCapturedStdout(), "0 1 2 3 4\n");
}

TEST(NormalPrint, Pair) {
  CaptureStdout();
  competitive::println(std::make_pair(1, 2.5));
  std::cout << std::flush;
  EXPECT_EQ(GetCapturedStdout(), "1 2.5\n");
}

TEST(NormalPrint, Tuple) {
  CaptureStdout();
  competitive::println(std::make_tuple(1, 2.5, "3"));
  std::cout << std::flush;
  EXPECT_EQ(GetCapturedStdout(), "1 2.5 3\n");
}

TEST(NormalPrint, TupleVector) {
  CaptureStdout();
  std::vector vec = {
      std::make_tuple(1, 2, 3),
      std::make_tuple(4, 5, 6),
  };
  competitive::println(vec);
  std::cout << std::flush;
  EXPECT_EQ(GetCapturedStdout(), "1 2 3 4 5 6\n");
}

TEST(NormalPrint, UseManip) {
  CaptureStdout();
  competitive::println(std::boolalpha, true);
  std::cout << std::flush;
  EXPECT_EQ(GetCapturedStdout(), "true\n");
}
