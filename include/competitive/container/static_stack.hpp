#pragma once
#include "competitive/utility/assert.hpp"
#include <bits/stdc++.h>

namespace competitive {
template <typename T, std::size_t Capacity> class static_stack {
  std::array<T, Capacity> elems_;
  std::size_t size_ = 0;

public:
  static_stack() = default;
  template <typename... Args> void emplace(Args&&... args) {
    CL_ASSERT(size_ < Capacity);
    elems_[size_++] = T(std::forward<Args>(args)...);
  }
  T pop() {
    CL_ASSERT(size_ > 0);
    return elems_[--size_];
  }
  std::size_t size() const {
    return size_;
  }
};
} // namespace competitive
