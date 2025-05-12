#pragma once
#include "bits/stdc++.h"

namespace common {
template <std::integral T> constexpr T abs(T const& v) {
  if constexpr (std::is_signed_v<T>) {
    return v < 0 ? -v : v;
  } else {
    return v;
  }
}
} // namespace common
