#pragma once
#include "boost/container/static_vector.hpp"
#include "competitive/io/print_base.hpp"
#include "competitive/utility/assert.hpp"
#include "competitive/utility/priority_queue.hpp"
#include <bits/stdc++.h>

namespace heuristic {
template <typename T, std::size_t Capacity,
          common::priority p = common::priority::greater>
class static_priority_container {
  boost::container::static_vector<T, Capacity> cont;
  std::function<bool(T const&, T const&)> comp;

public:
  template <typename Proj = std::identity>
  static_priority_container(Proj proj = {})
      : cont{}, comp([proj](T const& a, T const& b) {
          if constexpr (p == common::priority::less) {
            return proj(a) < proj(b);
          } else {
            return proj(a) > proj(b);
          }
        }) {}
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
  template <typename... Args> void emplace(Args&&... args) {
    push(T(std::forward<Args>(args)...));
  }
  auto begin() const {
    return cont.begin();
  }
  auto end() const {
    return cont.end();
  }
  std::size_t size() const {
    return cont.size();
  }
  void clear() {
    cont.clear();
  }
};
} // namespace heuristic
