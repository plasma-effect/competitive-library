#pragma once
#include "competitive/container/dual_array.hpp"
#include "competitive/utility.hpp"

namespace competitive {
namespace internal {
template <typename T>
void local_update(std::optional<T>& base, std::optional<T> a,
                  std::optional<T> b) {
  if (a && b) {
    if (!base) {
      base = *a + *b;
    } else {
      base = std::min(*base, *a + *b);
    }
  }
}
template <typename T> void local_update(T& base, T a, T b) {
  base = std::min(base, a + b);
}
} // namespace internal
template <typename T> void warshall_floyd(dual_array<T>& data) {
  auto [N, d1] = data.dimensions();
  CL_ASSERT(N == d1);
  for (auto k : irange(N)) {
    for (auto i : irange(N)) {
      for (auto j : irange(N)) {
        internal::local_update(data(i, j), data(i, k), data(k, j));
      }
    }
  }
}
} // namespace competitive
