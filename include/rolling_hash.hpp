#pragma once
#include "boost/multiprecision/cpp_int.hpp"
#include "utility.hpp"
#include <bits/stdc++.h>

namespace common {
namespace internal {
inline std::int64_t make_base() {
  std::uniform_int_distribution<std::int64_t> dist(2, 2LL << 50);
  std::random_device device{};
  return dist(device);
}
template <typename T>
inline std::vector<T> make_pow(T base, T mod, std::size_t N) {
  std::vector<T> ret(N + 1);
  ret[0] = 1;
  for (auto i : common::irange(N)) {
    ret[i + 1] = (ret[i] * base) % mod;
  }
  return ret;
}
} // namespace internal
template <char Min, char Max, std::size_t MaxSize = 100'000>
class rolling_hash {
#ifdef __GNUC__
  using int_t = __int128_t;
#else
  using int_t = boost::multiprecision::int128_t;
#endif
  static int_t base() {
    static const int_t b = internal::make_base();
    return b;
  }
  static int_t mod() { return (1LL << 61) - 1; }
  static const std::vector<int_t>& get_pow() {
    static const auto pow = internal::make_pow(base(), mod(), MaxSize);
    return pow;
  }
  std::vector<int_t> hashes;
  std::size_t size;

public:
  template <typename Rng>
  rolling_hash(Rng&& rng) : hashes(), size(std::size(rng)) {
    int_t hash = 0;
    hashes.reserve(size + 1);
    hashes.emplace_back(hash);
    for (auto c : rng) {
      assert(Min <= c && c <= Max);
      hash *= base();
      hash += c - Min + 1;
      hash %= mod();
      hashes.emplace_back(hash);
    }
  }
  class subhash_t {
    const rolling_hash& parent;
    std::size_t first, len;

  public:
    subhash_t(const rolling_hash& p, std::size_t f, std::size_t s)
        : parent(p), first(f), len(s) {}
    int_t hash() const {
      const auto p = rolling_hash::get_pow()[len];
      const auto& hashes = parent.hashes;
      auto h = (hashes[first + len] - hashes[first] * p) % mod();
      return h >= 0 ? h : h + mod();
    }
    friend class rolling_hash;

    bool operator==(const subhash_t& rhs) const {
      return len == rhs.len && hash() == rhs.hash();
    }
    bool operator!=(const subhash_t& rhs) const { return !(*this == rhs); }
  };
  subhash_t subhash(std::size_t first,
                    std::size_t len = common::max_v<std::size_t>) const {
    assert(first <= size);
    len = std::min(len, size - first);
    return subhash_t{*this, first, len};
  }
  bool operator==(const rolling_hash& rhs) const {
    return size == rhs.size && hashes.back() == rhs.hashes.back();
  }
  bool operator!=(const rolling_hash& rhs) const { return !(*this == rhs); }
};
} // namespace common
