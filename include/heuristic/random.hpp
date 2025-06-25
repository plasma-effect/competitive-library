#pragma once
#include <bits/stdc++.h>

namespace heuristic {
namespace internal {
inline std::mt19937& get_common_engine() {
  thread_local std::mt19937 engine{};
  return engine;
}
template <typename T, typename... Args> auto make_distribution(Args&&... args) {
  auto& engine = get_common_engine();
  T dist(std::forward<Args>(args)...);
  return [&engine, dist]() mutable {
    return dist(engine);
  };
}
} // namespace internal
template <typename T> auto make_uniform_int_distribution(T min, T max) {
  using type = std::uniform_int_distribution<T>;
  return internal::make_distribution<type>(min, max);
}
template <typename T> auto make_uniform_int_distribution(T max) {
  return make_uniform_int_distribution<T>(0, max);
}
template <typename T> auto make_uniform_real_distribution(T min, T max) {
  using type = std::uniform_real_distribution<T>;
  return internal::make_distribution<type>(min, max);
}
template <typename T> auto make_uniform_real_distribution(T max) {
  return make_uniform_real_distribution<T>(0, max);
}
inline auto make_bernoulli_distribution(double p = 0.5) {
  using type = std::bernoulli_distribution;
  return internal::make_distribution<type>(p);
}
template <std::input_iterator Ite>
auto make_discrete_distribution(const Ite& first, const Ite& last) {
  using type = std::discrete_distribution<std::size_t>;
  return internal::make_distribution<type>(first, last);
}
template <std::ranges::input_range Rng>
auto make_discrete_distribution(const Rng& rng) {
  return make_discrete_distribution(rng.begin(), rng.end());
}
inline auto make_discrete_distribution(std::initializer_list<double> list) {
  return make_discrete_distribution(list.begin(), list.end());
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
