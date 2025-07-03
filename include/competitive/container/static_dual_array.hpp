#pragma once
#include "competitive/io/print_base.hpp"
#include "competitive/utility/assert.hpp"
#include <bits/stdc++.h>

namespace competitive::container {
template <typename T, std::size_t H, std::size_t W> class static_dual_array {
  std::array<std::array<T, W>, H> inside_;

public:
  static_dual_array() : inside_{} {};
  template <std::integral Int0, std::integral Int1>
  T& operator()(Int0 i0, Int1 i1) {
    CL_ASSERT(std::cmp_greater_equal(i0, 0) && std::cmp_less(i0, H));
    CL_ASSERT(std::cmp_greater_equal(i1, 0) && std::cmp_less(i1, W));
    return inside_[i0][i1];
  }
  template <std::integral Int0, std::integral Int1>
  T const& operator()(Int0 i0, Int1 i1) const {
    CL_ASSERT(std::cmp_greater_equal(i0, 0) && std::cmp_less(i0, H));
    CL_ASSERT(std::cmp_greater_equal(i1, 0) && std::cmp_less(i1, W));
    return inside_[i0][i1];
  }
  template <std::integral Int0, std::integral Int1> T& at(Int0 i0, Int1 i1) {
    if (std::cmp_less(i0, 0) || std::cmp_greater_equal(i0, H)) [[unlikely]] {
      throw std::out_of_range(
          "argument 1 of static_dual_array::at is out of range");
    } else if (std::cmp_less(i1, 0) || std::cmp_greater_equal(i1, W))
        [[unlikely]] {
      throw std::out_of_range(
          "argument 2 of static_dual_array::at is out of range");
    }
    return inside_[i0][i1];
  }
  template <std::integral Int0, std::integral Int1>
  T const& at(Int0 i0, Int1 i1) const {
    if (std::cmp_less(i0, 0) || std::cmp_greater_equal(i0, H)) [[unlikely]] {
      throw std::out_of_range(
          "argument 1 of static_dual_array::at is out of range");
    } else if (std::cmp_less(i1, 0) || std::cmp_greater_equal(i1, W))
        [[unlikely]] {
      throw std::out_of_range(
          "argument 2 of static_dual_array::at is out of range");
    }
    return inside_[i0][i1];
  }

  std::pair<std::size_t, std::size_t> dimensions() const {
    return {H, W};
  }
  std::size_t size() const {
    return H * W;
  }
  friend common::internal::print_base_t&
  operator<<(common::internal::print_base_t& pb, static_dual_array const& ar) {
    return pb << ar.inside_;
  }
};
}
