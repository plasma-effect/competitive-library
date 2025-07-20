#include "competitive/heuristic/random.hpp"
#include <measurement.hpp>

namespace {
using types = ::measurement::Types<heuristic::xorshift, std::mt19937,
                                   std::mt19937_64, std::minstd_rand>;
struct NameSelector {
  template <typename T> static std::string GetName(std::size_t) {
    if constexpr (std::is_same_v<T, heuristic::xorshift>) {
      return "heuristic::xorshift";
    } else if constexpr (std::is_same_v<T, std::mt19937>) {
      return "std::mt19937";
    } else if constexpr (std::is_same_v<T, std::mt19937_64>) {
      return "std::mt19937_64";
    } else if constexpr (std::is_same_v<T, std::minstd_rand>) {
      return "std::minstd_rand";
    }
  }
};
constexpr int N = 1'000'000;
} // namespace

template <typename Engine> class RandomMeasure : public ::measurement::Measure {
protected:
  using generator = heuristic::random_engine_generator<Engine>;
};
TYPED_MEASURE_SUITE(RandomMeasure, types, NameSelector);

TYPED_MEASURE(RandomMeasure, UniformIntDistribution) {
  auto dist = TestFixture::generator::uniform_int_distribution(10);
  int sum = 0;
  for (int i = 0; i < N; ++i) {
    sum += dist();
  }
  MEASURE_DUMMY(sum);
}

TYPED_MEASURE(RandomMeasure, UniformRealDistribution) {
  auto dist = TestFixture::generator::uniform_real_distribution(2.0);
  double sum = 0;
  for (int i = 0; i < N; ++i) {
    sum += dist();
  }
  MEASURE_DUMMY(sum);
}

TYPED_MEASURE(RandomMeasure, GenerateCanonical) {
  double sum = 0;
  for (int i = 0; i < N; ++i) {
    sum += TestFixture::generator::generate_canonical();
  }
  MEASURE_DUMMY(sum);
}

TYPED_MEASURE(RandomMeasure, EqualProbabilityDistribution) {
  auto dist = TestFixture::generator::bernoulli_distribution();
  int count = 0;
  for (int i = 0; i < N; ++i) {
    if (dist()) {
      ++count;
    }
  }
  MEASURE_DUMMY(count);
}

TYPED_MEASURE(RandomMeasure, NonEqualProbabilityDistribution3) {
  auto dist = TestFixture::generator::bernoulli_distribution(0.75);
  int count = 0;
  for (int i = 0; i < N; ++i) {
    if (dist()) {
      ++count;
    }
  }
  MEASURE_DUMMY(count);
}

TYPED_MEASURE(RandomMeasure, NonEqualProbabilityDistribution9) {
  auto dist = TestFixture::generator::bernoulli_distribution(0.1);
  int count = 0;
  for (int i = 0; i < N; ++i) {
    if (dist()) {
      ++count;
    }
  }
  MEASURE_DUMMY(count);
}
