#pragma once
#include "boost/container/static_vector.hpp"
#include "competitive/io/print_base.hpp"
#include "competitive/utility/assert.hpp"
#include "competitive/utility/priority_queue.hpp"
#include <bits/stdc++.h>

namespace heuristic {
namespace internal {
template <typename T, std::size_t Capacity, typename Proj, typename Comp>
class static_priority_container {
  using compare_t = competitive::internal::projected_compare<T, Proj, Comp>;
  boost::container::static_vector<T, Capacity> cont;
  compare_t comp;

public:
  static_priority_container(Proj p, Comp c) : cont{}, comp{p, c} {}
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
} // namespace internal
template <typename T, std::size_t Capacity, typename Proj = std::identity>
auto make_static_priority_container(competitive::internal::greater_t,
                                    Proj proj = {}) {
  return internal::static_priority_container<T, Capacity, Proj, std::greater<>>(
      proj, {});
}
template <typename T, std::size_t Capacity, typename Proj = std::identity>
auto make_static_priority_container(competitive::internal::less_t,
                                    Proj proj = {}) {
  return internal::static_priority_container<T, Capacity, Proj, std::less<>>(
      proj, {});
}
template <typename T, std::size_t Capacity, typename Proj = std::identity>
auto make_static_priority_container(Proj proj = {})
  requires(!competitive::internal::is_priority_tag<Proj>)
{
  return internal::static_priority_container<T, Capacity, Proj, std::greater<>>(
      proj, {});
}
} // namespace heuristic
