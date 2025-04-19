#include "rolling_hash.hpp"
#include "gtest/gtest.h"

TEST(RollingHash, Parent) {
  using hash_t = common::rolling_hash<'a', 'z'>;
  std::string s0 = "abc";
  std::string s1 = "abcd";
  std::string s2 = "abd";
  hash_t h0(s0);
  hash_t h1(s0);
  hash_t h2(s1);
  hash_t h3(s2);
  EXPECT_EQ(h0, h1);
  EXPECT_NE(h0, h2);
  EXPECT_NE(h0, h3);
}

TEST(RollingHash, UsingViews) {
  using hash_t = common::rolling_hash<'a', 'z'>;
  std::string s0 = "abc";
  std::string s1 = "cba";
  hash_t h0(s0);
  hash_t h1(s1 | std::views::reverse);
  EXPECT_EQ(h0, h1);
}

TEST(RollingHash, SubHash) {
  using hash_t = common::rolling_hash<'a', 'z'>;
  std::string s0 = "abcabc";
  hash_t h0(s0);
  auto sh0 = h0.subhash(0, 3);
  auto sh1 = h0.subhash(1, 3);
  auto sh2 = h0.subhash(3, 3);
  auto sh3 = h0.subhash(0);
  auto sh4 = h0.subhash(3);
  EXPECT_NE(sh0, sh1);
  EXPECT_EQ(sh0, sh2) << int64_t(sh0.hash()) << " " << int64_t(sh2.hash());
  EXPECT_NE(sh0, sh3);
  EXPECT_EQ(sh0, sh4);
}
