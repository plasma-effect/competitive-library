#include "competitive/heuristic/random.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

TEST(HeuristicRandom, MakeUniformIntDistribution1) {
  auto results = test_utils::async([] {
    auto dist = heuristic::make_uniform_int_distribution(3);
    std::array<int, 5> result{};
    for (int c = 0; c < 10000; ++c) {
      auto v = dist();
      if (v < 0 || v >= 4) {
        ++result[4];
      } else {
        ++result[v];
      }
    }
    return result;
  });
  EXPECT_NE(results[0], 0);
  EXPECT_NE(results[1], 0);
  EXPECT_NE(results[2], 0);
  EXPECT_NE(results[3], 0);
  EXPECT_EQ(results[4], 0);
}

TEST(HeuristicRandom, MakeUniformIntDistribution2) {
  auto results = test_utils::async([] {
    auto dist = heuristic::make_uniform_int_distribution(0, 3);
    std::array<int, 5> result{};
    for (int c = 0; c < 10000; ++c) {
      auto v = dist();
      if (v < 0 || v >= 4) {
        ++result[4];
      } else {
        ++result[v];
      }
    }
    return result;
  });
  EXPECT_NE(results[0], 0);
  EXPECT_NE(results[1], 0);
  EXPECT_NE(results[2], 0);
  EXPECT_NE(results[3], 0);
  EXPECT_EQ(results[4], 0);
}

TEST(HeuristicRandom, MakeUniformRealDistribution1) {
  EXPECT_TRUE(test_utils::async([] {
    auto dist = heuristic::make_uniform_real_distribution(4.0);
    std::array<bool, 4> flag{};
    for (int c = 0; c < 10000; ++c) {
      auto v = dist();
      if (v < 0.0 || v >= 4.0) {
        return false;
      }
      auto i = static_cast<int>(v);
      flag[i] = true;
    }
    return std::ranges::all_of(flag, [](bool f) { return f; });
  }));
}

TEST(HeuristicRandom, MakeUniformRealDistribution2) {
  EXPECT_TRUE(test_utils::async([] {
    auto dist = heuristic::make_uniform_real_distribution(0.0, 4.0);
    std::array<bool, 4> flag{};
    for (int c = 0; c < 10000; ++c) {
      auto v = dist();
      if (v < 0.0 || v >= 4.0) {
        return false;
      }
      auto i = static_cast<int>(v);
      flag[i] = true;
    }
    return std::ranges::all_of(flag, [](bool f) { return f; });
  }));
}

TEST(HeuristicRandom, MakeBernoulliDistribution0) {
  EXPECT_TRUE(test_utils::async([] {
    auto dist = heuristic::make_bernoulli_distribution();
    std::array<bool, 2> flag{};
    for (int c = 0; c < 10000; ++c) {
      flag[dist()] = true;
    }
    return std::ranges::all_of(flag, [](bool f) { return f; });
  }));
}

TEST(HeuristicRandom, MakeBernoulliDistribution1) {
  EXPECT_TRUE(test_utils::async([] {
    auto dist = heuristic::make_bernoulli_distribution(0.75);
    std::array<bool, 2> flag{};
    for (int c = 0; c < 10000; ++c) {
      flag[dist()] = true;
    }
    return std::ranges::all_of(flag, [](bool f) { return f; });
  }));
}

TEST(HeuristicRandom, MakeBernoulliDistributionExtreme) {
  std::array<bool, 2> flag{};
  test_utils::async([&flag] {
    auto dist = heuristic::make_bernoulli_distribution(1.0);
    for (int c = 0; c < 10000; ++c) {
      flag[dist()] = true;
    }
  });
  EXPECT_FALSE(flag[0]);
  EXPECT_TRUE(flag[1]);
}

TEST(HeuristicRandom, MakeDiscreteDistibutionIterator) {
  auto result = test_utils::async([] {
    std::array probabilities = {0.0, 0.1, 0.2, 0.3, 0.4};
    std::array<std::size_t, 6> count{};
    auto dist = heuristic::make_discrete_distribution(probabilities.begin(),
                                                      probabilities.end());
    for (int c = 0; c < 10000; ++c) {
      auto v = dist();
      if (v >= 5) {
        ++count[5];
      } else {
        ++count[v];
      }
    }
    return count;
  });
  EXPECT_EQ(result[0], 0);
  EXPECT_NE(result[1], 0);
  EXPECT_LT(result[1], result[2]);
  EXPECT_NE(result[2], 0);
  EXPECT_LT(result[2], result[3]);
  EXPECT_NE(result[3], 0);
  EXPECT_LT(result[3], result[4]);
  EXPECT_NE(result[4], 0);
  EXPECT_EQ(result[5], 0);
}

TEST(HeuristicRandom, MakeDiscreteDistibutionRange) {
  auto result = test_utils::async([] {
    std::array probabilities = {0.0, 0.1, 0.2, 0.3, 0.4};
    std::array<std::size_t, 6> count{};
    auto dist = heuristic::make_discrete_distribution(probabilities);
    for (int c = 0; c < 10000; ++c) {
      auto v = dist();
      if (v >= 5) {
        ++count[5];
      } else {
        ++count[v];
      }
    }
    return count;
  });
  EXPECT_EQ(result[0], 0);
  EXPECT_NE(result[1], 0);
  EXPECT_LT(result[1], result[2]);
  EXPECT_NE(result[2], 0);
  EXPECT_LT(result[2], result[3]);
  EXPECT_NE(result[3], 0);
  EXPECT_LT(result[3], result[4]);
  EXPECT_NE(result[4], 0);
  EXPECT_EQ(result[5], 0);
}

TEST(HeuristicRandom, MakeDiscreteDistibutionInitList) {
  auto result = test_utils::async([] {
    std::array<std::size_t, 6> count{};
    auto dist =
        heuristic::make_discrete_distribution({0.0, 0.1, 0.2, 0.3, 0.4});
    for (int c = 0; c < 10000; ++c) {
      auto v = dist();
      if (v >= 5) {
        ++count[5];
      } else {
        ++count[v];
      }
    }
    return count;
  });
  EXPECT_EQ(result[0], 0);
  EXPECT_NE(result[1], 0);
  EXPECT_LT(result[1], result[2]);
  EXPECT_NE(result[2], 0);
  EXPECT_LT(result[2], result[3]);
  EXPECT_NE(result[3], 0);
  EXPECT_LT(result[3], result[4]);
  EXPECT_NE(result[4], 0);
  EXPECT_EQ(result[5], 0);
}

TEST(HeuristicRandom, GenerateCanonical) {
  EXPECT_TRUE(test_utils::async([] {
    for (int c = 0; c < 10000; ++c) {
      auto v = heuristic::generate_canonical();
      if (v < 0.0 || v >= 1.0) {
        return false;
      }
    }
    return true;
  }));
}

TEST(HeuristicRandom, GenerateCanonicalThreadLocal) {
  constexpr int N = 0x100;
  auto first = test_utils::async([] {
    std::array<double, N> result{};
    for (auto& v : result) {
      v = heuristic::generate_canonical();
    }
    return result;
  });
  auto second = test_utils::async([] {
    std::array<double, N> result{};
    for (auto& v : result) {
      v = heuristic::generate_canonical();
    }
    return result;
  });
  EXPECT_EQ(first, second);
}

TEST(HeuristicRandom, ShuffleRng) {
  std::array<int, 8> base = {0, 1, 2, 3, 4, 5, 6, 7};
  auto [first, second] = test_utils::async([base] {
    auto first_rng = base;
    heuristic::shuffle(first_rng);
    auto second_rng = base;
    heuristic::shuffle(second_rng);
    return std::pair(first_rng, second_rng);
  });
  for (int i = 0; i < 8; ++i) {
    EXPECT_EQ(std::ranges::count(first, i), 1);
    EXPECT_EQ(std::ranges::count(second, i), 1);
  }
  EXPECT_NE(base, first);
  EXPECT_NE(base, second);
  EXPECT_NE(first, second);
}

TEST(HeuristicRandom, ShuffleIterator) {
  std::array<int, 8> base = {0, 1, 2, 3, 4, 5, 6, 7};
  auto [first, second] = test_utils::async([base] {
    auto first_rng = base;
    heuristic::shuffle(first_rng.begin(), first_rng.end());
    auto second_rng = base;
    heuristic::shuffle(second_rng.begin(), second_rng.end());
    return std::pair(first_rng, second_rng);
  });
  for (int i = 0; i < 8; ++i) {
    EXPECT_EQ(std::ranges::count(first, i), 1);
    EXPECT_EQ(std::ranges::count(second, i), 1);
  }
  EXPECT_NE(base, first);
  EXPECT_NE(base, second);
  EXPECT_NE(first, second);
}
