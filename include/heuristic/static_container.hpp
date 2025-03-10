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
} // namespace heuristic
