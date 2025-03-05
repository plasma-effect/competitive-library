#pragma once
#include "print_base.hpp"
#include <bits/stdc++.h>

namespace common {
namespace detail {
template <bool> void print(print_base_t&) {}
template <bool put_blank, typename T, typename... Ts>
void print(print_base_t& pb, T const& arg, Ts const&... args) {
  if constexpr (put_blank) {
    pb.print(" ");
  }
  pb.print(arg);
  print<!is_std_manip_v<std::remove_cv_t<T>>>(pb, args...);
}
} // namespace detail
inline void println() { std::cout << "\n"; }
template <typename... Ts> void println(Ts const&... args) {
  common::detail::print_base_t pb(std::cout);
  detail::print<false>(pb, args...);
  std::cout << "\n";
}
} // namespace common
