#pragma once
#include "boost/range/irange.hpp"
#include <bits/stdc++.h>

namespace common {
template <typename T> constexpr auto max_v = std::numeric_limits<T>::max();
template <typename T> constexpr auto min_v = std::numeric_limits<T>::min();

template <typename Integer>
struct integer_range : boost::integer_range<Integer>, std::ranges::view_base {
  using boost::integer_range<Integer>::integer_range;
};
template <typename Integer> integer_range<Integer> irange(Integer last) {
  return integer_range<Integer>(Integer(0), last);
}
template <typename Integer>
integer_range<Integer> irange(Integer first, Integer last) {
  return integer_range<Integer>(first, last);
}

template <typename T> using pair = std::pair<T, T>;

template <typename T> class dual_array {
  std::vector<T> inside_;
  std::size_t dim0, dim1;

public:
  dual_array(std::size_t d0, std::size_t d1)
      : inside_(d0 * d1), dim0(d0), dim1(d1) {}
  T& operator()(int i0, int i1) {
    assert(0 <= i0 && std::cmp_less(i0, dim0));
    assert(0 <= i1 && std::cmp_less(i1, dim1));
    return inside_[i0 * dim1 + i1];
  }
  T const& operator()(int i0, int i1) const {
    assert(0 <= i0 && std::cmp_less(i0, dim0));
    assert(0 <= i1 && std::cmp_less(i1, dim1));
    return inside_[i0 * dim1 + i1];
  }
  T& operator()(std::size_t i0, std::size_t i1) {
    assert(std::cmp_less(i0, dim0));
    assert(std::cmp_less(i1, dim1));
    return inside_[i0 * dim1 + i1];
  }
  T const& operator()(std::size_t i0, std::size_t i1) const {
    assert(std::cmp_less(i0, dim0));
    assert(std::cmp_less(i1, dim1));
    return inside_[i0 * dim1 + i1];
  }
  common::pair<std::size_t> dimensions() const { return {dim0, dim1}; }
  std::size_t size() const { return dim0 * dim1; }
};

template <typename T, typename F = std::greater<>>
using priority_queue = std::priority_queue<T, std::vector<T>, F>;
} // namespace common
