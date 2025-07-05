#pragma once
#include "competitive/heuristic/random.hpp"
#include <bits/stdc++.h>

namespace heuristic {
using time_t = std::chrono::milliseconds;
inline auto get_time() {
  using namespace std::chrono;
  thread_local const auto start = system_clock::now();
  return duration_cast<milliseconds>(system_clock::now() - start);
}
namespace internal {

template <std::int64_t time_limit_ms, std::size_t update_frequency,
          typename Derived>
class time_control_base {
  std::size_t update_count_;

public:
  operator bool() {
    if (++update_count_ == update_frequency) {
      update_count_ = 0;
      auto current = get_time();
      static_cast<Derived&>(*this).update(current);
      return current.count() < time_limit_ms;
    } else {
      return true;
    }
  }
};
} // namespace internal

template <std::int64_t time_limit_ms, std::size_t update_frequency = 1>
struct time_control_t : internal::time_control_base<
                            time_limit_ms, update_frequency,
                            time_control_t<time_limit_ms, update_frequency>> {
  void update(time_t const&) {}
};

template <std::int64_t time_limit_ms, std::int64_t start_temperature,
          std::int64_t end_temperature, std::size_t update_frequency = 1,
          typename Engine = std::minstd_rand>
class time_control_with_annealing
    : public internal::time_control_base<
          time_limit_ms, update_frequency,
          time_control_with_annealing<time_limit_ms, start_temperature,
                                      end_temperature, update_frequency,
                                      Engine>> {
  using basetype = internal::time_control_base<
      time_limit_ms, update_frequency,
      time_control_with_annealing<time_limit_ms, start_temperature,
                                  end_temperature, update_frequency, Engine>>;
  using generator = random_engine_generator<Engine>;
  static constexpr std::size_t particle = 1 << 8;
  static constexpr std::array<double, particle> make_log_table() {
    std::array<double, particle> table;
    table[0] = -std::numeric_limits<double>::infinity();
    for (std::size_t i = 1; i < particle; ++i) {
      table[i] = std::log(double(i) / double(particle));
    }
    return table;
  }
  static constexpr std::array<double, time_limit_ms> make_temperature_table() {
    std::array<double, time_limit_ms> table;
    double T1 = end_temperature;
    double dT = double(start_temperature) / double(end_temperature);
    for (int i = 0; i < time_limit_ms; ++i) {
      double nt = i / double(time_limit_ms);
      table[i] = T1 * std::pow(dT, 1 - nt);
    }
    return table;
  }
  static constexpr auto log_table = make_log_table();
  static constexpr auto temp_table = make_temperature_table();

  std::function<std::size_t()> dist;
  double T;

public:
  time_control_with_annealing()
      : dist(generator::uniform_int_distribution(particle - 1)),
        T(temp_table[0]) {}
  void update(time_t const& current) {
    T = temp_table[current.count()];
  }

  bool transition_check(double diff) {
    if (diff > 0) {
      return true;
    } else {
      auto p = dist();
      return log_table[p] * T < diff;
    }
  }
};
} // namespace heuristic
