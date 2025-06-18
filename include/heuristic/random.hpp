#pragma once
#include <bits/stdc++.h>

namespace heuristic {
namespace internal {
inline std::mt19937& get_common_engine() {
  thread_local std::mt19937 engine{};
  return engine;
}
} // namespace internal
template <typename T> auto make_uniform_int_distribution(T min, T max) {
  auto& engine = internal::get_common_engine();
  std::uniform_int_distribution<T> dist(min, max);
  return [&engine, dist]() mutable {
    return dist(engine);
  };
}
template <typename T> auto make_uniform_int_distribution(T max) {
  return make_uniform_int_distribution<T>(0, max);
}
inline double generate_canonical() {
  auto& engine = internal::get_common_engine();
  constexpr auto digits = std::numeric_limits<double>::digits;
  return std::generate_canonical<double, digits>(engine);
}
template <typename Rng> void shuffle(Rng& rng) {
  std::ranges::shuffle(rng, internal::get_common_engine());
}
template <std::random_access_iterator It> void shuffle(It first, It last) {
  std::shuffle(first, last, internal::get_common_engine());
}
} // namespace heuristic
