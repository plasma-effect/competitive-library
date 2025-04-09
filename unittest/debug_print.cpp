#include "debug_print.hpp"
#include <gtest/gtest.h>
using testing::internal::CaptureStderr;
using testing::internal::GetCapturedStderr;

TEST(DebugPrint, Integer1) {
  CaptureStderr();
  debug::println(1);
  EXPECT_EQ(GetCapturedStderr(), "1\n");
}

TEST(DebugPrint, Integer2) {
  CaptureStderr();
  debug::println(1, 2);
  EXPECT_EQ(GetCapturedStderr(), "1 2\n");
}

TEST(DebugPrint, IntVector) {
  CaptureStderr();
  std::vector vec = {1, 2, 3};
  debug::println(vec);
  EXPECT_EQ(GetCapturedStderr(), "{1, 2, 3}\n");
}

TEST(DebugPrint, Irange) {
  CaptureStderr();
  debug::println(common::irange(5));
  EXPECT_EQ(GetCapturedStderr(), "{0, 1, 2, 3, 4}\n");
}

TEST(DebugPrint, Pair) {
  CaptureStderr();
  debug::println(std::make_pair(1, 2.5));
  EXPECT_EQ(GetCapturedStderr(), "(1, 2.5)\n");
}

TEST(DebugPrint, Tuple) {
  CaptureStderr();
  debug::println(std::make_tuple(1, 2.5, "3"));
  EXPECT_EQ(GetCapturedStderr(), "(1, 2.5, 3)\n");
}

TEST(DebugPrint, TupleVector) {
  CaptureStderr();
  std::vector vec = {
      std::make_tuple(1, 2, 3),
      std::make_tuple(4, 5, 6),
  };
  debug::println(vec);
  EXPECT_EQ(GetCapturedStderr(), "{(1, 2, 3), (4, 5, 6)}\n");
}

TEST(DebugPrint, UseManip) {
  CaptureStderr();
  debug::println(std::boolalpha, true);
  EXPECT_EQ(GetCapturedStderr(), "true\n");
}
