#pragma once
#include "utility.hpp"

namespace graph {
namespace detail {
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
} // namespace detail
template <typename T> void warshall_floyd(common::dual_array<T>& data) {
  auto [N, d1] = data.dimensions();
  assert(N == d1);
  for (auto k : boost::irange(N)) {
    for (auto i : boost::irange(N)) {
      for (auto j : boost::irange(N)) {
        detail::local_update(data(i, j), data(i, k), data(k, j));
      }
    }
  }
}
} // namespace graph
