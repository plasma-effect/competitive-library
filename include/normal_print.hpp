#pragma once
#include "print_base.hpp"
#include <bits/stdc++.h>

namespace common {
namespace detail {
template <typename T>
constexpr bool is_std_manip_v =
    std::is_same_v<T, decltype(std::setbase(std::declval<int>()))> ||
    std::is_same_v<T, decltype(std::setfill(std::declval<char>()))> ||
    std::is_same_v<T, decltype(std::setprecision(std::declval<int>()))> ||
    std::is_same_v<T, decltype(std::setw(std::declval<int>()))> ||
    std::is_convertible_v<T, std::ios_base& (*)(std::ios_base&)>;
template <bool> void print(print_detail::print_base_t&) {}
template <bool put_blank, typename T, typename... Ts>
void print(print_detail::print_base_t& pb, T const& arg, Ts const&... args) {
  if constexpr (put_blank) {
    pb.print(" ");
  }
  pb.print(arg);
  print<!is_std_manip_v<std::remove_cv_t<T>>>(pb, args...);
}
} // namespace detail
inline void println() { std::cout << "\n"; }
template <typename... Ts> void println(Ts const&... args) {
  print_detail::print_base_t pb(std::cout);
  detail::print<false>(pb, args...);
  std::cout << "\n";
}
} // namespace common
