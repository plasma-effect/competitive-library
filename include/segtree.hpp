#pragma once
#include "atcoder/all"
#include "numeric.hpp"

namespace common {
namespace detail {
template <auto monoid> using value_t = typename decltype(monoid)::value_t;
} // namespace detail
template <auto monoid>
using segtree = atcoder::segtree<detail::value_t<monoid>, monoid, monoid>;
template <typename T> using add_segtree = segtree<numeric::plus<T>>;
template <typename T> using mul_segtree = segtree<numeric::multiplies<T>>;
template <typename T> using max_segtree = segtree<numeric::max<T>>;

template <auto m0, auto m1>
using lazy_segtree = atcoder::lazy_segtree<detail::value_t<m0>, m0, m0,
                                           detail::value_t<m1>, m1, m1, m1>;
} // namespace common
