#pragma once
#include "competitive/utility/assert.hpp"
#include <bits/stdc++.h>

namespace competitive {
template <typename T, std::size_t Capacity> class static_queue {
  std::array<T, Capacity> elems_;
  T* first_;
  T* last_;
  std::size_t size_;

public:
  static_queue()
      : elems_{}, first_(elems_.begin()), last_(elems_.begin()), size_() {}
  template <typename... Args> void emplace(Args&&... args) {
    CL_ASSERT(size_ < Capacity);
    *last_ = T(std::forward<Args>(args)...);
    if (++last_ == elems_.end()) {
      last_ = elems_.begin();
    }
    ++size_;
  }
  T pop() {
    CL_ASSERT(size_ > 0);
    auto ret = std::move(*first_);
    if (++first_ == elems_.end()) {
      first_ = elems_.begin();
    }
    --size_;
    return ret;
  }
  std::size_t size() const {
    return size_;
  }
};
} // namespace competitive
