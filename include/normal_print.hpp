#pragma once
#include "print_base.hpp"
#include <bits/stdc++.h>

namespace common::internal {
template <bool> void print(print_base_t&) {}
template <bool put_blank, typename T, typename... Ts>
void print(print_base_t& pb, T const& arg, Ts const&... args) {
  if constexpr (put_blank) {
    pb << " ";
  }
  pb << arg;
  common::internal::print<!is_std_manip_v<std::remove_cv_t<T>>>(pb, args...);
}
} // namespace common::internal
namespace common {
inline void println() { std::cout << "\n"; }
template <typename... Ts> void println(Ts const&... args) {
  common::internal::print_base_t pb(std::cout);
  common::internal::print<false>(pb, args...);
  std::cout << "\n";
}
} // namespace common
