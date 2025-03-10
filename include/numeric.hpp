#pragma once
#include "utility.hpp"
#include <bits/stdc++.h>

namespace numeric {
template <typename T, typename F> struct monoid_t {
  using value_t = T;
  T e_;
  F op_;
  constexpr monoid_t(T e, F op) : e_(e), op_(op) {}
  constexpr T operator()() const { return e_; }
  constexpr T operator()(T const& lhs, T const& rhs) const {
    return op_(lhs, rhs);
  }
};
template <typename T> constexpr monoid_t plus{T(0), std::plus<>()};
template <typename T> constexpr monoid_t multiplies{T(1), std::multiplies<>()};
template <typename T>
constexpr monoid_t min{common::max_v<T>,
                       static_cast<T const& (*)(T const&, T const&)>(std::min)};
template <typename T>
constexpr monoid_t max{common::min_v<T>,
                       static_cast<T const& (*)(T const&, T const&)>(std::max)};
} // namespace numeric
