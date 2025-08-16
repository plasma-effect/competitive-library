#include "competitive/io/print_base.hpp"
#include "competitive/utility/irange.hpp"
#include <gtest/gtest.h>

TEST(PrintBase, String) {
  std::stringstream ss;
  common::internal::print_base_t base(ss);
  std::string str = "str";
  base << str;
  EXPECT_EQ(ss.str(), "str");
}

TEST(PrintBase, StringView) {
  std::stringstream ss;
  common::internal::print_base_t base(ss);
  std::string_view str = "str";
  base << str;
  EXPECT_EQ(ss.str(), "str");
}

TEST(PrintBase, CharPtr) {
  std::stringstream ss;
  common::internal::print_base_t base(ss);
  const char* str = "str";
  base << str;
  EXPECT_EQ(ss.str(), "str");
}

TEST(PrintBase, CharLiteral) {
  std::stringstream ss;
  common::internal::print_base_t base(ss);
  base << "str";
  EXPECT_EQ(ss.str(), "str");
}

TEST(PrintBase, Integer) {
  std::stringstream ss;
  common::internal::print_base_t base(ss);
  base << 1;
  base << 2u;
  EXPECT_EQ(ss.str(), "12");
}

TEST(PrintBase, Floating) {
  std::stringstream ss;
  common::internal::print_base_t base(ss);
  base << 1.5;
  EXPECT_EQ(ss.str(), "1.5");
}

TEST(PrintBase, ExecuteManip) {
  std::stringstream ss;
  common::internal::print_base_t base(ss);
  base << std::setprecision(3);
  base << 0.1234;
  EXPECT_EQ(ss.str(), "0.123");
}

TEST(PrintBase, AtCoderStaticModint) {
  std::stringstream ss;
  common::internal::print_base_t base(ss);
  atcoder::static_modint<7> mod(2);
  base << mod;
  EXPECT_EQ(ss.str(), "2");
}

TEST(PrintBase, CommonRange) {
  std::stringstream ss;
  common::internal::print_base_t base(ss);
  base << common::irange(5);
  EXPECT_EQ(ss.str(), "0 1 2 3 4");
}

TEST(PrintBase, StdVector) {
  std::stringstream ss;
  common::internal::print_base_t base(ss);
  std::vector vec = {0, 2, 4};
  base << vec;
  EXPECT_EQ(ss.str(), "0 2 4");
}

TEST(PrintBase, StaticArray) {
  std::stringstream ss;
  common::internal::print_base_t base(ss);
  int ar[] = {1, 3, 5};
  base << ar;
  EXPECT_EQ(ss.str(), "1 3 5");
}

TEST(PrintBase, Pair) {
  std::stringstream ss;
  common::internal::print_base_t base(ss);
  std::pair p(1, "2");
  base << p;
  EXPECT_EQ(ss.str(), "1 2");
}

TEST(PrintBase, Tuple) {
  std::stringstream ss;
  common::internal::print_base_t base(ss);
  std::tuple t(1, "2", 3u);
  base << t;
  EXPECT_EQ(ss.str(), "1 2 3");
}

TEST(PrintBase, Optional) {
  std::stringstream ss;
  common::internal::print_base_t base(ss);
  std::optional<int> a;
  base << a;
  a = 1;
  base << a;
  EXPECT_EQ(ss.str(), "<nullopt>1");
}

TEST(PrintBase, OptionalVector) {
  std::stringstream ss;
  common::internal::print_base_t base(ss);
  std::vector<std::optional<int>> vec(3);
  vec[0] = 1;
  vec[2] = 3;
  base << vec;
  EXPECT_EQ(ss.str(), "1 <nullopt> 3");
}

TEST(PrintBase, SetRangeDec) {
  std::stringstream ss;
  common::internal::print_base_t base(ss);
  std::vector vec = {0, 1, 2};
  base.set_range_decolater("{", "}", ",");
  base << vec;
  EXPECT_EQ(ss.str(), "{0,1,2}");
}

TEST(PrintBase, SetTupleDec) {
  std::stringstream ss;
  common::internal::print_base_t base(ss);
  std::tuple tpl(0, 1, 2);
  base.set_tuple_decolater("(", ")", ",");
  base << tpl;
  EXPECT_EQ(ss.str(), "(0,1,2)");
}

TEST(PrintBase, SetCombDec) {
  std::stringstream ss;
  common::internal::print_base_t base(ss);
  std::vector vec = {std::pair(1, 2), std::pair(3, 4)};
  base.set_range_decolater("{", "}", ", ");
  base.set_tuple_decolater("(", ")", ", ");
  base << vec;
  EXPECT_EQ(ss.str(), "{(1, 2), (3, 4)}");
}
