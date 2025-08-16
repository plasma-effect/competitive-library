#pragma once
#include <bits/stdc++.h>

#ifdef LOCAL_DEBUG
namespace common::debug::internal {
[[noreturn]] inline void assertion_fail(const char* expr) {
  auto st = std::stacktrace::current(1);
  std::cerr << "assertion failed: \"" << expr << "\"\n";
  std::cerr << "where: " << st[0].description();
  std::cerr << ": " << st[0].source_line() << "\n";
  for (auto it = std::next(st.begin()); it != st.end(); ++it) {
    if (it->source_line() != 0) {
      std::cerr << " from: " << it->description();
      std::cerr << ": " << it->source_line() << "\n";
    }
  }
  std::cerr << std::flush;
  throw std::logic_error("assertion failed");
}
} // namespace common::debug::internal
#define CL_ASSERT(expr)                                                        \
  (static_cast<bool>(expr) ? void(0)                                           \
                           : common::debug::internal::assertion_fail(#expr))
#else
#define CL_ASSERT(expr) assert(expr)
#endif
