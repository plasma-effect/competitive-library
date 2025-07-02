#pragma once
#include "atcoder/all"
#include <future>

namespace test_utils {
template <typename Func> auto async(Func func) {
  return std::async(std::launch::async, func).get();
}
} // namespace test_utils
