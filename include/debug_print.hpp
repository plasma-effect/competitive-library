#pragma once
#include "print_base.hpp"
#include <bits/stdc++.h>

namespace debug::internal {
template <bool> void print(common::internal::print_base_t&) {}
template <bool put_blank, typename T, typename... Ts>
void print(common::internal::print_base_t& pb, T const& arg,
           Ts const&... args) {
  if constexpr (put_blank) {
    pb << " ";
  }
  pb << arg;
  debug::internal::print<
      !common::internal::is_std_manip_v<std::remove_cv_t<T>>>(pb, args...);
}
} // namespace debug::internal
namespace debug {
inline void println() { std::cerr << std::endl; }
template <typename... Ts> void println(Ts const&... args) {
  common::internal::print_base_t pb(std::cerr);
  pb.set_range_prefix("{");
  pb.set_range_suffix("}");
  pb.set_range_delim(", ");
  pb.set_tuple_prefix("(");
  pb.set_tuple_suffix(")");
  pb.set_tuple_delim(", ");
  debug::internal::print<false>(pb, args...);
  std::cerr << std::endl;
}
} // namespace debug
