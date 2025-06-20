#pragma once
#include "atcoder/all"
#include "numeric.hpp"

namespace common {
template <auto monoid>
using segtree =
    atcoder::segtree<numeric::internal::value_t<monoid>, monoid, monoid>;
template <typename T> using add_segtree = segtree<numeric::plus<T>>;
template <typename T> using mul_segtree = segtree<numeric::multiplies<T>>;
template <typename T> using max_segtree = segtree<numeric::max<T>>;

template <auto monoid, auto mapping>
using lazy_segtree =
    atcoder::lazy_segtree<numeric::internal::value_t<monoid>, monoid, monoid,
                          numeric::internal::value_t<mapping>, mapping, mapping,
                          mapping>;
} // namespace common
