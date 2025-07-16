#include "competitive/heuristic/persistent_array.hpp"
#include "measure_utils.hpp"
#include <measurement.hpp>
#include <random>
using heuristic::persistent_array;
using measure_utils::add;
using measure_utils::generate;

namespace {
using types = ::measurement::Types<int, double, bool>;
}

template <typename T>
class PersistentArrayMeasure : public ::measurement::Measure {};
TYPED_MEASURE_SUITE(PersistentArrayMeasure, types,
                    measure_utils::DefaultNameSelector);

constexpr std::size_t N = 1 << 12;
TYPED_MEASURE(PersistentArrayMeasure, UpdateEveryTime) {
  using array_t = persistent_array<TypeParam, N>;
  constexpr std::size_t U = 1;
  measure_utils::xorshift engine;
  array_t ar;
  std::vector<array_t> vec;
  vec.reserve(N / U);
  Start();
  for (std::size_t idx = 0, c = 0; c < N / U; ++c) {
    for (std::size_t u = 0; u < U; ++u, idx += 3) {
      ar.update(idx & (N - 1), generate<TypeParam>(engine));
    }
    vec.emplace_back(ar);
  }
  Stop();
  for (auto const& a : vec) {
    TypeParam v{};
    for (std::size_t i = 0; i < N; ++i) {
      v = add(v, a.get(i));
    }
    MEASURE_DUMMY(v);
  }
}

TYPED_MEASURE(PersistentArrayMeasure, Update4Times) {
  constexpr std::size_t U = 4;
  using array_t = persistent_array<TypeParam, N>;
  measure_utils::xorshift engine;
  array_t ar;
  std::vector<array_t> vec;
  vec.reserve(N / U);
  Start();
  for (std::size_t idx = 0, c = 0; c < N / U; ++c) {
    for (std::size_t u = 0; u < U; ++u, idx += 3) {
      ar.update(idx & (N - 1), generate<TypeParam>(engine));
    }
    vec.emplace_back(ar);
  }
  Stop();
  for (auto const& a : vec) {
    TypeParam v{};
    for (std::size_t i = 0; i < N; ++i) {
      v = add(v, a.get(i));
    }
    MEASURE_DUMMY(v);
  }
}

TYPED_MEASURE(PersistentArrayMeasure, Update16Times) {
  constexpr std::size_t U = 16;
  using array_t = persistent_array<TypeParam, N>;
  measure_utils::xorshift engine;
  array_t ar;
  std::vector<array_t> vec;
  vec.reserve(N / U);
  Start();
  for (std::size_t idx = 0, c = 0; c < N / U; ++c) {
    for (std::size_t u = 0; u < U; ++u, idx += 3) {
      ar.update(idx & (N - 1), generate<TypeParam>(engine));
    }
    vec.emplace_back(ar);
  }
  Stop();
  for (auto const& a : vec) {
    TypeParam v{};
    for (std::size_t i = 0; i < N; ++i) {
      v = add(v, a.get(i));
    }
    MEASURE_DUMMY(v);
  }
}

TYPED_MEASURE(PersistentArrayMeasure, Update64Times) {
  constexpr std::size_t U = 64;
  using array_t = persistent_array<TypeParam, N>;
  measure_utils::xorshift engine;
  array_t ar;
  std::vector<array_t> vec;
  vec.reserve(N / U);
  Start();
  for (std::size_t idx = 0, c = 0; c < N / U; ++c) {
    for (std::size_t u = 0; u < U; ++u, idx += 3) {
      ar.update(idx & (N - 1), generate<TypeParam>(engine));
    }
    vec.emplace_back(ar);
  }
  Stop();
  for (auto const& a : vec) {
    TypeParam v{};
    for (std::size_t i = 0; i < N; ++i) {
      v = add(v, a.get(i));
    }
    MEASURE_DUMMY(v);
  }
}
