#include "competitive/io/debug_print.hpp"
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

TEST(DebugPrint, DualArray) {
  CaptureStderr();
  common::dual_array<int> ar(2, 3);
  ar(0, 0) = 1;
  ar(0, 1) = 2;
  ar(0, 2) = 3;
  ar(1, 0) = 4;
  ar(1, 1) = 5;
  ar(1, 2) = 6;
  debug::println(ar);
  EXPECT_EQ(GetCapturedStderr(), "{{1, 2, 3}, {4, 5, 6}}\n");
}

TEST(DebugPrint, BooleanDualArray) {
  CaptureStderr();
  common::dual_array<bool> ar(2, 3);
  ar(0, 0) = true;
  ar(0, 1) = false;
  ar(0, 2) = true;
  ar(1, 0) = false;
  ar(1, 1) = true;
  ar(1, 2) = false;
  debug::println(ar);
  EXPECT_EQ(GetCapturedStderr(), "{{1, 0, 1}, {0, 1, 0}}\n");
}
TEST(DebugPrint, BooleanDualArrayElem) {
  CaptureStderr();
  common::dual_array<bool> ar(2, 2);
  ar(0, 0) = true;
  ar(0, 1) = false;
  ar(1, 0) = false;
  ar(1, 1) = true;
  debug::println(ar(0, 0), ar(0, 1), ar(1, 0), ar(1, 1));
  std::cout << std::flush;
  EXPECT_EQ(GetCapturedStderr(), "1 0 0 1\n");
}

TEST(DebugPrint, DebugPrintMacro) {
  CaptureStderr();
  DEBUG_PRINT(1, 2);
#ifdef LOCAL_DEBUG
  EXPECT_EQ(GetCapturedStderr(), "98: 1 2\n");
#else
  EXPECT_EQ(GetCapturedStderr(), "");
#endif
}

TEST(DebugPrint, DebugPrintMacroNone) {
  CaptureStderr();
  DEBUG_PRINT();
#ifdef LOCAL_DEBUG
  EXPECT_EQ(GetCapturedStderr(), "108:\n");
#else
  EXPECT_EQ(GetCapturedStderr(), "");
#endif
}
