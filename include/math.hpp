#pragma once
#include "bits/stdc++.h"
#include "utility.hpp"

namespace common {
template <typename T> std::vector<T> make_factorial_array(std::size_t max) {
  std::vector<T> ret(max + 1);
  ret[0] = T(1);
  for (auto i : common::irange(max)) {
    ret[i + 1] = ret[i] * T(i + 1);
  }
  return ret;
}
} // namespace common
