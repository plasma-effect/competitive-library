#pragma once
#include "assert.hpp"
#include <bits/stdc++.h>

namespace common {
template <typename T> constexpr auto max_v = std::numeric_limits<T>::max();
template <typename T> constexpr auto min_v = std::numeric_limits<T>::min();

template <std::integral Int> auto irange(Int first, Int last) {
  CL_ASSERT(std::cmp_less_equal(first, last));
  return std::views::iota(first, last);
}
template <std::integral Int> auto irange(Int last) {
  return irange(Int(0), last);
}

template <typename T> using pair = std::pair<T, T>;

template <typename T> class dual_array {
  std::vector<T> inside_;
  std::size_t dim0, dim1;

public:
  dual_array(std::size_t d0, std::size_t d1)
      : inside_(d0 * d1), dim0(d0), dim1(d1) {}
  template <std::integral Int0, std::integral Int1>
  T& operator()(Int0 i0, Int1 i1) {
    CL_ASSERT(std::cmp_greater_equal(i0, 0) && std::cmp_less(i0, dim0));
    CL_ASSERT(std::cmp_greater_equal(i1, 0) && std::cmp_less(i1, dim1));
    return inside_[i0 * dim1 + i1];
  }
  template <std::integral Int0, std::integral Int1>
  T const& operator()(Int0 i0, Int1 i1) const {
    CL_ASSERT(std::cmp_greater_equal(i0, 0) && std::cmp_less(i0, dim0));
    CL_ASSERT(std::cmp_greater_equal(i1, 0) && std::cmp_less(i1, dim1));
    return inside_[i0 * dim1 + i1];
  }
  common::pair<std::size_t> dimensions() const {
    return {dim0, dim1};
  }
  std::size_t size() const {
    return dim0 * dim1;
  }
};

template <> class dual_array<bool> : public dual_array<std::uint8_t> {
public:
  using dual_array<std::uint8_t>::dual_array;
};

template <typename T, typename F = std::greater<>>
using priority_queue = std::priority_queue<T, std::vector<T>, F>;

constexpr bool is_debug() {
#ifdef LOCAL_DEBUG
  return true;
#else
  return false;
#endif
}
} // namespace common
