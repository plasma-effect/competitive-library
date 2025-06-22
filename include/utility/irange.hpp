#pragma once
#include "assert.hpp"

namespace common {
template <std::integral Int> auto irange(Int first, Int last) {
  CL_ASSERT(std::cmp_less_equal(first, last));
  return std::views::iota(first, last);
}
template <std::integral Int> auto irange(Int last) {
  return irange(Int(0), last);
}
} // namespace common
