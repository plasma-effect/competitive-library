#pragma once
#include "competitive/utility/assert.hpp"
#include <bits/stdc++.h>

namespace common {
template <typename T> class dual_array {
  std::vector<T> inside_;
  std::size_t dim0, dim1;

public:
  dual_array(std::size_t d0, std::size_t d1)
      : inside_(d0 * d1), dim0(d0), dim1(d1) {}
  template <std::integral Int0, std::integral Int1>
  T& operator()(Int0 i0, Int1 i1) {
    CL_ASSERT(std::cmp_greater_equal(i0, 0) && std::cmp_less(i0, dim0));
    CL_ASSERT(std::cmp_greater_equal(i1, 0) && std::cmp_less(i1, dim1));
    return inside_[i0 * dim1 + i1];
  }
  template <std::integral Int0, std::integral Int1>
  T const& operator()(Int0 i0, Int1 i1) const {
    CL_ASSERT(std::cmp_greater_equal(i0, 0) && std::cmp_less(i0, dim0));
    CL_ASSERT(std::cmp_greater_equal(i1, 0) && std::cmp_less(i1, dim1));
    return inside_[i0 * dim1 + i1];
  }
  template <std::integral Int0, std::integral Int1> T& at(Int0 i0, Int1 i1) {
    if (std::cmp_less(i0, 0) || std::cmp_greater_equal(i0, dim0)) [[unlikely]] {
      throw std::out_of_range("argument 1 of dual_array::at is out of range");
    } else if (std::cmp_less(i1, 0) || std::cmp_greater_equal(i1, dim1))
        [[unlikely]] {
      throw std::out_of_range("argument 2 of dual_array::at is out of range");
    }
    return inside_[i0 * dim1 + i1];
  }
  template <std::integral Int0, std::integral Int1>
  T const& at(Int0 i0, Int1 i1) const {
    if (std::cmp_less(i0, 0) || std::cmp_greater_equal(i0, dim0)) [[unlikely]] {
      throw std::out_of_range("argument 1 of dual_array::at is out of range");
    } else if (std::cmp_less(i1, 0) || std::cmp_greater_equal(i1, dim1))
        [[unlikely]] {
      throw std::out_of_range("argument 2 of dual_array::at is out of range");
    }
    return inside_[i0 * dim1 + i1];
  }

  std::pair<std::size_t, std::size_t> dimensions() const {
    return {dim0, dim1};
  }
  std::size_t size() const {
    return dim0 * dim1;
  }
};

namespace internal {
struct bool_ploxy {
  bool v = false;
  operator bool() const {
    return v;
  }
  bool_ploxy& operator=(bool u) {
    v = u;
    return *this;
  }
};
} // namespace internal
template <> class dual_array<bool> : public dual_array<internal::bool_ploxy> {
public:
  using dual_array<internal::bool_ploxy>::dual_array;
};
} // namespace common
