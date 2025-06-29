#pragma once
#include <bits/stdc++.h>

namespace common {
namespace internal {
template <typename T, typename Proj, typename Comp> struct projected_compare {
  Proj proj;
  Comp comp;
  bool operator()(T const& a, T const& b) const {
    return comp(proj(a), proj(b));
  }
};

} // namespace internal
enum class priority { greater, less };
template <typename T, priority p = priority::less> class priority_queue {
  std::priority_queue<T, std::vector<T>,
                      std::function<bool(T const&, T const&)>>
      queue;

public:
  template <typename Proj = std::identity>
  priority_queue(Proj proj = {})
      : queue([proj](T const& a, T const& b) {
          if constexpr (p == priority::less) {
            return proj(a) > proj(b);
          } else {
            return proj(a) < proj(b);
          }
        }) {}
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

} // namespace common
