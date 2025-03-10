#pragma once
#include <bits/stdc++.h>

namespace heuristic {
auto get_time() {
  using namespace std::chrono;
  thread_local const auto start = system_clock::now();
  return duration_cast<milliseconds>(system_clock::now() - start);
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
} // namespace heuristic
