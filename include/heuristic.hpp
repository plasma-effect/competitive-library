#pragma once
#include "boost/container/static_vector.hpp"
#include "utility.hpp"
#include <bits/stdc++.h>

namespace heuristic {
auto get_time() {
  using namespace std::chrono;
  thread_local const auto start = system_clock::now();
  return duration_cast<milliseconds>(system_clock::now() - start);
}

namespace detail {
std::mt19937& get_common_engine() {
  thread_local std::mt19937 engine{};
  return engine;
}
} // namespace detail
template <typename T> auto make_uniform_int_distribution(T min, T max) {
  auto& engine = detail::get_common_engine();
  std::uniform_int_distribution<T> dist(min, max);
  return [&engine, dist]() mutable { return dist(engine); };
}
double generate_canonical() {
  auto& engine = detail::get_common_engine();
  constexpr auto digits = std::numeric_limits<double>::digits;
  return std::generate_canonical<double, digits>(engine);
}
template <typename Rng> void shuffle(Rng& rng) {
  std::ranges::shuffle(rng, detail::get_common_engine());
}
template <std::random_access_iterator It> void shuffle(It first, It last) {
  std::shuffle(first, last, detail::get_common_engine());
}

class time_control_t {
  std::chrono::milliseconds time_limit_;
  std::size_t update_frequency_;
  double T1, dT, T;
  std::size_t update_count;
  std::chrono::milliseconds current;

  void update_temperature() {
    auto nt = double(current.count()) / double(time_limit_.count());
    T = T1 * std::pow(dT, 1 - nt);
  }

public:
  time_control_t(std::chrono::milliseconds time_limit, std::size_t ufreq = 1,
                 double t0 = 2000, double t1 = 600)
      : time_limit_(time_limit), update_frequency_(ufreq), T1(t1), dT(t0 / t1),
        T{}, update_count(), current(get_time()) {
    update_temperature();
  }
  operator bool() {
    if (++update_count == update_frequency_) {
      update_count = 0;
      current = get_time();
      update_temperature();
    }
    return current < time_limit_;
  }

  double annealing_threshold(double diff) { return std::exp(diff / T); }
  bool transition_check(double diff) {
    if (diff > 0) {
      return true;
    } else {
      return generate_canonical() < annealing_threshold(diff);
    }
  }
};

// For Beam Search
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

// For Grid Graph
template <typename T, std::size_t H, std::size_t W> class grid_bfs_queue {
  using internal_t = std::pair<int, common::dual_array<int>>;
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
          std::pair(0, common::dual_array<int>(H, W)));
    }
    ++grid_ptr->first;
  }
  ~grid_bfs_queue() { grids.push_back(std::move(grid_ptr)); }
  void push(int i, int j, T&& arg) { queue.emplace(i, j, std::move(arg)); }
  void push(int i, int j, const T& arg) { queue.emplace(i, j, arg); }
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
