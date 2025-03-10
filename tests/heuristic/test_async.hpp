#pragma once

template <typename Func> auto test_async(Func func) {
  return std::async(std::launch::async, func).get();
}
