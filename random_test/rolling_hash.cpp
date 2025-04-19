#include "rolling_hash.hpp"
#include "random_test_base.hpp"
#include "gtest/gtest.h"

class RollingHashRandom : public test_utils::RandomTestBase,
                          public ::testing::WithParamInterface<int> {
  static inline std::mt19937 engine;

protected:
  static constexpr std::size_t N = 100'000;
  virtual std::mt19937& get_random_engine() override { return engine; }
  std::string make_random_string() {
    auto dist = make_uniform_int_distribution('a', 'z');
    std::string s;
    s.reserve(N);
    for ([[maybe_unused]] auto _ : common::irange(N)) {
      s.push_back(dist());
    }
    return s;
  }
};

TEST_P(RollingHashRandom, Simple) {
  using hash_t = common::rolling_hash<'a', 'z'>;
  auto base = make_random_string();
  auto s = base;
  auto get_index = make_uniform_int_distribution(N);
  auto get_char = make_uniform_int_distribution('a', 'z');
  std::set<std::size_t> diff;
  hash_t hash(base);
  for ([[maybe_unused]] auto _ : common::irange(1000)) {
    auto i = get_index();
    auto c = get_char();
    s[i] = c;
    if (diff.contains(i) && s[i] == base[i]) {
      diff.erase(i);
    } else if (s[i] != base[i]) {
      diff.emplace(i);
    }
    hash_t h(s);
    if (diff.size()) {
      ASSERT_NE(hash, h) << "base = " << base.substr(0, 10)
                         << "..., s = " << s.substr(0, 10) << "...";
    } else {
      ASSERT_EQ(hash, h) << "base = " << base.substr(0, 10)
                         << "..., s = " << s.substr(0, 10) << "...";
    }
  }
}

TEST_P(RollingHashRandom, SubStr) {
  using hash_t = common::rolling_hash<'a', 'z'>;
  auto str0 = make_random_string();
  auto str1 = make_random_string();
  std::string_view view0(str0), view1(str1);
  hash_t hash0(str0), hash1(str1);
  for (auto i : common::irange(10)) {
    for (auto j : common::irange(10)) {
      auto v0 = view0.substr(i, 10000);
      auto v1 = view1.substr(j, 10000);
      if (v0 != v1) {
        ASSERT_NE(hash0.subhash(i, 10000), hash1.subhash(j, 10000))
            << "v0 = " << v0.substr(0, 10) << "..., v1 = " << v1.substr(0, 10)
            << "...";
      } else {
        ASSERT_EQ(hash0.subhash(i, 10000), hash1.subhash(j, 10000))
            << "v0 = " << v0.substr(0, 10) << "..., v1 = " << v1.substr(0, 10)
            << "...";
      }
    }
  }
}

INSTANTIATE_TEST_CASE_P(RandomCaseTest, RollingHashRandom,
                        ::testing::Range(0, 20));
