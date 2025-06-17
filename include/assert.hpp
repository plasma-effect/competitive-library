#pragma once
#include <bits/stdc++.h>

#ifdef LOCAL_DEBUG
namespace debug::internal {
[[noreturn]] inline void assertion_fail(const char* expr) {
  auto st = std::stacktrace::current(1);
  std::cerr << "assertion failed: \"" << expr << "\"\nwhere: " << st[0] << "\n";
  for (auto it = std::next(st.begin()); it != st.end(); ++it) {
    if (it->source_line() != 0) {
      std::cerr << " from: " << *it << "\n";
    }
  }
  std::cerr << std::flush;
  throw std::logic_error("assertion failed");
}
} // namespace debug::internal
#define CL_ASSERT(expr)                                                        \
  (static_cast<bool>(expr) ? void(0) : debug::internal::assertion_fail(#expr))
#else
#define CL_ASSERT(expr) assert(expr)
#endif
