#pragma once
#include "boost/container/static_vector.hpp"
#include <bits/stdc++.h>

namespace heuristic {
template <typename T, std::size_t Capacity, typename Compare = std::greater<>>
class static_priority_container {
  boost::container::static_vector<T, Capacity> cont;
  Compare comp;

public:
  static_priority_container(Compare = {}) : cont{}, comp{} {}
  void push(T value) {
    if (cont.size() < Capacity) {
      cont.push_back(value);
      std::ranges::push_heap(cont, comp);
    } else if (comp(value, cont.front())) {
      std::ranges::pop_heap(cont, comp);
      std::swap(cont.back(), value);
      std::ranges::push_heap(cont, comp);
    }
  }
  auto begin() const { return cont.begin(); }
  auto end() const { return cont.end(); }
};

template <typename T, std::size_t H, std::size_t W> class static_dual_array {
  std::array<std::array<T, W>, H> inside_;

public:
  static_dual_array() : inside_{} {};
  template <std::integral Int0, std::integral Int1>
  T& operator()(Int0 i0, Int1 i1) {
    assert(std::cmp_greater_equal(i0, 0) && std::cmp_less(i0, H));
    assert(std::cmp_greater_equal(i1, 0) && std::cmp_less(i1, W));
    return inside_[i0][i1];
  }
  template <std::integral Int0, std::integral Int1>
  T const& operator()(Int0 i0, Int1 i1) const {
    assert(std::cmp_greater_equal(i0, 0) && std::cmp_less(i0, H));
    assert(std::cmp_greater_equal(i1, 0) && std::cmp_less(i1, W));
    return inside_[i0][i1];
  }
  std::pair<std::size_t, std::size_t> dimensions() const { return {H, W}; }
  std::size_t size() const { return H * W; }
};
} // namespace heuristic
