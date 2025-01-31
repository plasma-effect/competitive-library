#include "print_base.hpp"
#include "gtest/gtest.h"

TEST(PrintBase, String) {
  std::stringstream ss;
  print_detail::print_base_t base(ss);
  std::string str = "str";
  base.print(str);
  EXPECT_EQ(ss.str(), "str");
}

TEST(PrintBase, StringView) {
  std::stringstream ss;
  print_detail::print_base_t base(ss);
  std::string_view str = "str";
  base.print(str);
  EXPECT_EQ(ss.str(), "str");
}

TEST(PrintBase, CharPtr) {
  std::stringstream ss;
  print_detail::print_base_t base(ss);
  const char* str = "str";
  base.print(str);
  EXPECT_EQ(ss.str(), "str");
}

TEST(PrintBase, CharLiteral) {
  std::stringstream ss;
  print_detail::print_base_t base(ss);
  base.print("str");
  EXPECT_EQ(ss.str(), "str");
}

TEST(PrintBase, Integer) {
  std::stringstream ss;
  print_detail::print_base_t base(ss);
  base.print(1);
  base.print(2u);
  EXPECT_EQ(ss.str(), "12");
}

TEST(PrintBase, Floating) {
  std::stringstream ss;
  print_detail::print_base_t base(ss);
  base.print(1.5);
  EXPECT_EQ(ss.str(), "1.5");
}

TEST(PrintBase, ExecuteManip) {
  std::stringstream ss;
  print_detail::print_base_t base(ss);
  base.print(std::setprecision(3));
  base.print(0.1234);
  EXPECT_EQ(ss.str(), "0.123");
}

TEST(PrintBase, AtCoderStaticModint) {
  std::stringstream ss;
  print_detail::print_base_t base(ss);
  atcoder::static_modint<7> mod(2);
  base.print(mod);
  EXPECT_EQ(ss.str(), "2");
}

TEST(PrintBase, CommonRange) {
  std::stringstream ss;
  print_detail::print_base_t base(ss);
  base.print(common::irange(5));
  EXPECT_EQ(ss.str(), "0 1 2 3 4");
}

TEST(PrintBase, StdVector) {
  std::stringstream ss;
  print_detail::print_base_t base(ss);
  std::vector vec = {0, 2, 4};
  base.print(vec);
  EXPECT_EQ(ss.str(), "0 2 4");
}

TEST(PrintBase, StaticArray) {
  std::stringstream ss;
  print_detail::print_base_t base(ss);
  int ar[] = {1, 3, 5};
  base.print(ar);
  EXPECT_EQ(ss.str(), "1 3 5");
}

TEST(PrintBase, Pair) {
  std::stringstream ss;
  print_detail::print_base_t base(ss);
  std::pair p(1, "2");
  base.print(p);
  EXPECT_EQ(ss.str(), "1 2");
}

TEST(PrintBase, Tuple) {
  std::stringstream ss;
  print_detail::print_base_t base(ss);
  std::tuple t(1, "2", 3u);
  base.print(t);
  EXPECT_EQ(ss.str(), "1 2 3");
}

TEST(PrintBase, SetRangeDec) {
  std::stringstream ss;
  print_detail::print_base_t base(ss);
  std::vector vec = {0, 1, 2};
  base.set_range_prefix("{");
  base.set_range_suffix("}");
  base.set_range_delim(",");
  base.print(vec);
  EXPECT_EQ(ss.str(), "{0,1,2}");
}

TEST(PrintBase, SetTupleDec) {
  std::stringstream ss;
  print_detail::print_base_t base(ss);
  std::tuple tpl(0, 1, 2);
  base.set_tuple_prefix("(");
  base.set_tuple_suffix(")");
  base.set_tuple_delim(",");
  base.print(tpl);
  EXPECT_EQ(ss.str(), "(0,1,2)");
}

TEST(PrintBase, SetCombDec) {
  std::stringstream ss;
  print_detail::print_base_t base(ss);
  std::vector vec = {std::pair(1, 2), std::pair(3, 4)};
  base.set_range_prefix("{");
  base.set_range_suffix("}");
  base.set_range_delim(", ");
  base.set_tuple_prefix("(");
  base.set_tuple_suffix(")");
  base.set_tuple_delim(", ");
  base.print(vec);
  EXPECT_EQ(ss.str(), "{(1, 2), (3, 4)}");
}
