#pragma once
#include <bits/stdc++.h>

namespace heuristic {
namespace detail {
std::mt19937& get_common_engine() {
  thread_local std::mt19937 engine{};
  return engine;
}
} // namespace detail

template <typename T> auto make_uniform_int_distribution(T min, T max) {
  auto& engine = detail::get_common_engine();
  std::uniform_int_distribution<T> dist(min, max);
  return [&engine, dist]() mutable { return dist(engine); };
}
double generate_canonical() {
  auto& engine = detail::get_common_engine();
  constexpr auto digits = std::numeric_limits<double>::digits;
  return std::generate_canonical<double, digits>(engine);
}
template <typename Rng> void shuffle(Rng& rng) {
  std::ranges::shuffle(rng, detail::get_common_engine());
}
template <std::random_access_iterator It> void shuffle(It first, It last) {
  std::shuffle(first, last, detail::get_common_engine());
}
} // namespace heuristic
