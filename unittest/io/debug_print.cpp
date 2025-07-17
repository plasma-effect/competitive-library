#include "competitive/io/debug_print.hpp"
#include "competitive/utility/irange.hpp"
#include <gtest/gtest.h>
using testing::internal::CaptureStderr;
using testing::internal::GetCapturedStderr;

TEST(DebugPrint, Integer1) {
  CaptureStderr();
  competitive::debug::println(1);
  EXPECT_EQ(GetCapturedStderr(), "1\n");
}

TEST(DebugPrint, Integer2) {
  CaptureStderr();
  competitive::debug::println(1, 2);
  EXPECT_EQ(GetCapturedStderr(), "1 2\n");
}

TEST(DebugPrint, IntVector) {
  CaptureStderr();
  std::vector vec = {1, 2, 3};
  competitive::debug::println(vec);
  EXPECT_EQ(GetCapturedStderr(), "{1, 2, 3}\n");
}

TEST(DebugPrint, Irange) {
  CaptureStderr();
  competitive::debug::println(competitive::irange(5));
  EXPECT_EQ(GetCapturedStderr(), "{0, 1, 2, 3, 4}\n");
}

TEST(DebugPrint, Pair) {
  CaptureStderr();
  competitive::debug::println(std::make_pair(1, 2.5));
  EXPECT_EQ(GetCapturedStderr(), "(1, 2.5)\n");
}

TEST(DebugPrint, Tuple) {
  CaptureStderr();
  competitive::debug::println(std::make_tuple(1, 2.5, "3"));
  EXPECT_EQ(GetCapturedStderr(), "(1, 2.5, 3)\n");
}

TEST(DebugPrint, TupleVector) {
  CaptureStderr();
  std::vector vec = {
      std::make_tuple(1, 2, 3),
      std::make_tuple(4, 5, 6),
  };
  competitive::debug::println(vec);
  EXPECT_EQ(GetCapturedStderr(), "{(1, 2, 3), (4, 5, 6)}\n");
}

TEST(DebugPrint, UseManip) {
  CaptureStderr();
  competitive::debug::println(std::boolalpha, true);
  EXPECT_EQ(GetCapturedStderr(), "true\n");
}

TEST(DebugPrint, DebugPrintMacro) {
  CaptureStderr();
  DEBUG_PRINT(1, 2);
#ifdef LOCAL_DEBUG
  EXPECT_EQ(GetCapturedStderr(), "62: 1 2\n");
#else
  EXPECT_EQ(GetCapturedStderr(), "");
#endif
}

TEST(DebugPrint, DebugPrintMacroNone) {
  CaptureStderr();
  DEBUG_PRINT();
#ifdef LOCAL_DEBUG
  EXPECT_EQ(GetCapturedStderr(), "72:\n");
#else
  EXPECT_EQ(GetCapturedStderr(), "");
#endif
}
