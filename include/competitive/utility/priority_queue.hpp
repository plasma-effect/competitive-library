#pragma once
#include <bits/stdc++.h>

namespace competitive {
namespace internal {
template <typename T, typename Proj, typename Comp> struct projected_compare {
  Proj proj;
  Comp comp;
  bool operator()(T const& a, T const& b) const {
    return comp(proj(a), proj(b));
  }
};
template <typename T, typename Proj, typename Comp> class priority_queue {
  using compare_t = projected_compare<T, Proj, Comp>;
  std::priority_queue<T, std::vector<T>, compare_t> queue;

public:
  priority_queue(Proj proj, Comp comp) : queue(compare_t{proj, comp}) {}
  std::size_t size() const {
    return queue.size();
  }
  T top() const {
    return queue.top();
  }
  void push(T const& v) {
    queue.push(v);
  }
  void push(T&& v) {
    queue.push(std::move(v));
  }
  template <typename... Args> void emplace(Args&&... args) {
    queue.emplace(std::forward<Args>(args)...);
  }
  void pop() {
    queue.pop();
  }
};
struct greater_t {};
struct less_t {};
template <typename T>
concept is_priority_tag =
    std::is_same_v<T, greater_t> || std::is_same_v<T, less_t>;
} // namespace internal
namespace priority {
constexpr internal::greater_t greater{};
constexpr internal::less_t less{};
} // namespace priority
template <typename T, typename Proj = std::identity>
auto make_priority_queue(internal::less_t, Proj proj = {}) {
  return internal::priority_queue<T, Proj, std::greater<>>(proj, {});
}
template <typename T, typename Proj = std::identity>
auto make_priority_queue(internal::greater_t, Proj proj = {}) {
  return internal::priority_queue<T, Proj, std::less<>>(proj, {});
}
template <typename T, typename Proj = std::identity>
auto make_priority_queue(Proj proj = {})
  requires(!internal::is_priority_tag<Proj>)
{
  return internal::priority_queue<T, Proj, std::greater<>>(proj, {});
}
} // namespace competitive
