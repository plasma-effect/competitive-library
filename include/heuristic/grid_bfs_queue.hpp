#pragma once
#include "heuristic/static_container.hpp"

namespace heuristic {
template <typename T, std::size_t H, std::size_t W> class grid_bfs_queue {
  using internal_t = std::pair<int, heuristic::static_dual_array<int, H, W>>;
  using internal_ptr = std::unique_ptr<internal_t>;
  static inline std::vector<internal_ptr> grids;
  internal_ptr grid_ptr;
  std::queue<std::tuple<int, int, T>> queue;
  bool check_front(bool pop_flag) {
    auto& [count, flags] = *grid_ptr;
    while (queue.size()) {
      auto& [i, j, v] = queue.front();
      if (std::cmp_less(i, 0) || std::cmp_greater_equal(i, H) ||
          std::cmp_less(j, 0) || std::cmp_greater_equal(j, W)) {
        queue.pop();
      } else if (flags(i, j) == count) {
        queue.pop();
      } else {
        if (pop_flag) {
          flags(i, j) = count;
        }
        return true;
      }
    }
    return false;
  }

public:
  grid_bfs_queue() : grid_ptr(), queue() {
    if (grids.size()) {
      grid_ptr = std::move(grids.back());
      grids.pop_back();
    } else {
      grid_ptr = std::make_unique<internal_t>(
          std::pair(0, heuristic::static_dual_array<int, H, W>()));
    }
    ++grid_ptr->first;
  }
  ~grid_bfs_queue() {
    grids.push_back(std::move(grid_ptr));
  }
  void push(int i, int j, T&& arg) {
    queue.emplace(i, j, std::move(arg));
  }
  void push(int i, int j, const T& arg) {
    queue.emplace(i, j, arg);
  }
  template <typename... Args> void emplace(int i, int j, Args&&... args) {
    push(i, j, T(std::forward<Args>(args)...));
  }
  std::optional<std::tuple<int, int, T>> pop() {
    if (check_front(true)) {
      auto&& ret = std::move(queue.front());
      queue.pop();
      return std::make_optional(std::move(ret));
    } else {
      return std::nullopt;
    }
  }
};
} // namespace heuristic
