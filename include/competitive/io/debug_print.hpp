#pragma once
#include "competitive/io/print_base.hpp"
#include <bits/stdc++.h>

namespace competitive::debug {
inline void println() {
  std::cerr << std::endl;
}
template <typename... Ts> void println(Ts const&... args) {
  competitive::internal::print_base_t pb(std::cerr);
  pb.set_range_decolater("{", "}", ", ");
  pb.set_tuple_decolater("(", ")", ", ");
  competitive::internal::print<false>(pb, args...);
  std::cerr << std::endl;
}
} // namespace competitive::debug
#ifdef LOCAL_DEBUG
#define CL_PP_STR_I(s) #s
#define CL_PP_STR(s) CL_PP_STR_I(s)
#define DEBUG_PRINT(...)                                                       \
  competitive::debug::println(CL_PP_STR(__LINE__) ":" __VA_OPT__(, )           \
                                  __VA_ARGS__)
#else
#define DEBUG_PRINT(...) (void)(0)
#endif
