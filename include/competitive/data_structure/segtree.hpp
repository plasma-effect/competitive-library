#pragma once
#include "atcoder/all"
#include "competitive/math/monoid.hpp"

namespace competitive {
namespace internal {
template <auto monoid> using value_t = typename decltype(monoid)::value_t;
}
template <auto monoid>
using segtree = atcoder::segtree<internal::value_t<monoid>, monoid, monoid>;
template <typename T> using add_segtree = segtree<math::plus<T>>;
template <typename T> using mul_segtree = segtree<math::multiplies<T>>;
template <typename T> using max_segtree = segtree<math::max<T>>;

template <auto monoid, auto mapping>
using lazy_segtree = atcoder::lazy_segtree<internal::value_t<monoid>, monoid,
                                           monoid, internal::value_t<mapping>,
                                           mapping, mapping, mapping>;
} // namespace competitive
