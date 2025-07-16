#include "competitive/heuristic/persistent_array.hpp"
#include "measure_utils.hpp"
#include <measurement.hpp>
#include <random>
using heuristic::persistent_array;
using measure_utils::add;
using measure_utils::generate;

namespace {
template <typename T, typename Span> struct TypePair {
  using value_t = T;
  static constexpr auto span = Span::value;
};
struct NameSelector {
  template <typename T> static std::string GetName(std::size_t) {
    constexpr const char* type =
        std::is_same_v<typename T::value_t, int>      ? "int"
        : std::is_same_v<typename T::value_t, double> ? "double"
                                                      : "bool";
    char buf[0x10];
    std::sprintf(buf, "%s%02zu", type, T::span);
    return std::string(buf);
  }
};
template <std::size_t I> using span_t = std::integral_constant<std::size_t, I>;
using value_types = ::measurement::Types<bool, int, double>;
using span_types =
    ::measurement::Types<span_t<1>, span_t<4>, span_t<16>, span_t<64>>;
using types = measure_utils::CartesianProductBase<TypePair, value_types,
                                                  span_types>::type;
} // namespace

template <typename T>
class PersistentArrayMeasure : public ::measurement::Measure {};
TYPED_MEASURE_SUITE(PersistentArrayMeasure, types, NameSelector);

constexpr std::size_t N = 1 << 12;
TYPED_MEASURE(PersistentArrayMeasure, UpdateSequenceOld) {
  using T = typename TypeParam::value_t;
  using array_t = persistent_array<T, N>;
  measure_utils::xorshift engine;
  array_t ar;
  std::vector<array_t> vec;
  vec.reserve(N / TypeParam::span);
  Start();
  for (std::size_t idx = 0, c = 0; c < N / TypeParam::span; ++c) {
    for (std::size_t u = 0; u < TypeParam::span; ++u, ++idx) {
      ar.update(idx & (N - 1), generate<T>(engine));
    }
    vec.emplace_back(ar);
  }
  Stop();
  for (auto const& a : vec) {
    T v{};
    for (std::size_t i = 0; i < N; ++i) {
      v = add(v, a.get(i));
    }
    MEASURE_DUMMY(v);
  }
}

TYPED_MEASURE(PersistentArrayMeasure, UpdateOtherOrderOld) {
  using T = typename TypeParam::value_t;
  using array_t = persistent_array<T, N>;
  measure_utils::xorshift engine;
  array_t ar;
  std::vector<array_t> vec;
  vec.reserve(N / TypeParam::span);
  Start();
  for (std::size_t idx = 0, c = 0; c < N / TypeParam::span; ++c) {
    for (std::size_t u = 0; u < TypeParam::span; ++u, idx += 3) {
      ar.update(idx & (N - 1), generate<T>(engine));
    }
    vec.emplace_back(ar);
  }
  Stop();
  for (auto const& a : vec) {
    T v{};
    for (std::size_t i = 0; i < N; ++i) {
      v = add(v, a.get(i));
    }
    MEASURE_DUMMY(v);
  }
}

TYPED_MEASURE(PersistentArrayMeasure, UpdateSequenceNew) {
  using T = typename TypeParam::value_t;
  using array_t = persistent_array<T, N>;
  measure_utils::xorshift engine;
  std::vector<array_t> vec(1);
  vec.reserve(N / TypeParam::span);
  Start();
  for (std::size_t idx = 0, c = 0; c < N / TypeParam::span; ++c) {
    for (std::size_t u = 0; u < TypeParam::span; ++u, ++idx) {
      vec.back().update(idx & (N - 1), generate<T>(engine));
    }
    vec.emplace_back(vec.back());
  }
  Stop();
  for (auto const& a : vec) {
    T v{};
    for (std::size_t i = 0; i < N; ++i) {
      v = add(v, a.get(i));
    }
    MEASURE_DUMMY(v);
  }
}

TYPED_MEASURE(PersistentArrayMeasure, UpdateOtherOrderNew) {
  using T = typename TypeParam::value_t;
  using array_t = persistent_array<T, N>;
  measure_utils::xorshift engine;
  std::vector<array_t> vec(1);
  vec.reserve(N / TypeParam::span);
  Start();
  for (std::size_t idx = 0, c = 0; c < N / TypeParam::span; ++c) {
    for (std::size_t u = 0; u < TypeParam::span; ++u, idx += 3) {
      vec.back().update(idx & (N - 1), generate<T>(engine));
    }
    vec.emplace_back(vec.back());
  }
  Stop();
  for (auto const& a : vec) {
    T v{};
    for (std::size_t i = 0; i < N; ++i) {
      v = add(v, a.get(i));
    }
    MEASURE_DUMMY(v);
  }
}

TYPED_MEASURE(PersistentArrayMeasure, ReadSequence) {
  using T = typename TypeParam::value_t;
  using array_t = persistent_array<T, N>;
  measure_utils::xorshift engine;
  array_t ar;
  std::vector<array_t> vec;
  vec.reserve(N / TypeParam::span);
  for (std::size_t idx = 0, c = 0; c < N / TypeParam::span; ++c) {
    for (std::size_t u = 0; u < TypeParam::span; ++u, ++idx) {
      ar.update(idx & (N - 1), generate<T>(engine));
    }
    vec.emplace_back(ar);
  }
  Start();
  T sum{};
  for (auto const& a : vec) {
    for (std::size_t i = 0; i < N; ++i) {
      sum = add(sum, a.get(i));
    }
  }
  Stop();
  MEASURE_DUMMY(sum);
}

TYPED_MEASURE(PersistentArrayMeasure, ReadOtherOrder) {
  using T = typename TypeParam::value_t;
  using array_t = persistent_array<T, N>;
  measure_utils::xorshift engine;
  array_t ar;
  std::vector<array_t> vec;
  vec.reserve(N / TypeParam::span);
  for (std::size_t idx = 0, c = 0; c < N / TypeParam::span; ++c) {
    for (std::size_t u = 0; u < TypeParam::span; ++u, ++idx) {
      ar.update(idx & (N - 1), generate<T>(engine));
    }
    vec.emplace_back(ar);
  }
  Start();
  T sum{};
  for (auto const& a : vec) {
    for (std::size_t i = 0; i < 3 * N; i += 3) {
      sum = add(sum, a.get(i & (N - 1)));
    }
  }
  Stop();
  MEASURE_DUMMY(sum);
}
