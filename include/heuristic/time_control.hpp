#pragma once
#include "heuristic/random.hpp"
#include <bits/stdc++.h>

namespace heuristic {
using time_t = std::chrono::milliseconds;
auto get_time() {
  using namespace std::chrono;
  thread_local const auto start = system_clock::now();
  return duration_cast<milliseconds>(system_clock::now() - start);
}
namespace internal {
template <typename Derived> class time_control_base {
  time_t time_limit_, current_;
  std::size_t update_frequency_, update_count_;

public:
  time_control_base(time_t time_limit, std::size_t ufreq = 1)
      : time_limit_(time_limit), current_(get_time()), update_frequency_(ufreq),
        update_count_() {}
  operator bool() {
    if (++update_count_ == update_frequency_) {
      update_count_ = 0;
      current_ = get_time();
      static_cast<Derived&>(*this).update(time_limit_, current_);
    }
    return current_ < time_limit_;
  }
};
} // namespace internal

struct time_control_t : internal::time_control_base<time_control_t> {
  void update(time_t const&, time_t const&) {}
  using time_control_base::time_control_base;
};

class time_control_with_annealing
    : public internal::time_control_base<time_control_with_annealing> {
  using time_control_base::time_control_base;

public:
  double T1, dT, T;
  time_control_with_annealing(time_t time_limit, std::size_t ufreq, double t0,
                              double t1)
      : time_control_base(time_limit, ufreq), T1(t1), dT(t0 / t1), T(t0) {}
  time_control_with_annealing(time_t time_limit, double t0, double t1)
      : time_control_with_annealing(time_limit, 1, t0, t1) {}
  void update(time_t const& time_limit, time_t const& current) {
    auto nt = double(current.count()) / double(time_limit.count());
    T = T1 * std::pow(dT, 1 - nt);
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
