#include "competitive/data_structure/segtree.hpp"
#include "measure_utils.hpp"
#include <measurement.hpp>
using measure_utils::generate;
using measure_utils::xorshift;

namespace {
using types = ::measurement::Types<int, double>;
constexpr int N = 1 << 16;
} // namespace

template <typename T> class SegtreeMeasure : public measurement::Measure {
protected:
  static inline xorshift engine;
};
TYPED_MEASURE_SUITE(SegtreeMeasure, types, measure_utils::DefaultNameSelector);

TYPED_MEASURE(SegtreeMeasure, SegTreeSet) {
  competitive::add_segtree<TypeParam> tree(N);
  Start();
  for (int i = 0; i < N; ++i) {
    tree.set(i, generate<TypeParam>(TestFixture::engine));
  }
  Stop();
  constexpr int sizes[] = {1, 4, 16, 1 << 8, 1 << 16};
  for (int s : sizes) {
    for (int i = 0; i + s <= N; ++i) {
      MEASURE_DUMMY(tree.prod(i, i + s));
    }
  }
}

TYPED_MEASURE(SegtreeMeasure, SegTreeProd) {
  competitive::add_segtree<TypeParam> tree(N);
  for (int i = 0; i < N; ++i) {
    tree.set(i, generate<TypeParam>(TestFixture::engine));
  }
  Start();
  constexpr int sizes[] = {1, 4, 16, 1 << 8, 1 << 16};
  for (int s : sizes) {
    for (int i = 0; i + s <= N; ++i) {
      MEASURE_DUMMY(tree.prod(i, i + s));
    }
  }
  Stop();
}

TYPED_MEASURE(SegtreeMeasure, LazySegTreeSet) {
  constexpr auto monoid = competitive::min<TypeParam>;
  constexpr auto mapping = competitive::plus<TypeParam>;
  competitive::lazy_segtree<monoid, mapping> tree(N);
  Start();
  for (int i = 0; i < N; ++i) {
    tree.set(i, generate<TypeParam>(TestFixture::engine));
  }
  Stop();
  constexpr int sizes[] = {1, 4, 16, 1 << 8, 1 << 16};
  for (int s : sizes) {
    for (int i = 0; i + s <= N; ++i) {
      MEASURE_DUMMY(tree.prod(i, i + s));
    }
  }
}

TYPED_MEASURE(SegtreeMeasure, LazySegTreeProd) {
  constexpr auto monoid = competitive::min<TypeParam>;
  constexpr auto mapping = competitive::plus<TypeParam>;
  competitive::lazy_segtree<monoid, mapping> tree(N);
  for (int i = 0; i < N; ++i) {
    tree.set(i, generate<TypeParam>(TestFixture::engine));
  }
  Start();
  constexpr int sizes[] = {1, 4, 16, 1 << 8, 1 << 16};
  for (int s : sizes) {
    for (int i = 0; i + s <= N; ++i) {
      MEASURE_DUMMY(tree.prod(i, i + s));
    }
  }
  Stop();
}

TYPED_MEASURE(SegtreeMeasure, LazySegTreeApply) {
  constexpr auto monoid = competitive::min<TypeParam>;
  constexpr auto mapping = competitive::plus<TypeParam>;
  competitive::lazy_segtree<monoid, mapping> tree(N);
  for (int i = 0; i < N; ++i) {
    tree.set(i, generate<TypeParam>(TestFixture::engine));
  }
  Start();
  constexpr int sizes[] = {1, 4, 16, 1 << 8, 1 << 16};
  for (int s : sizes) {
    for (int i = 0; i + s <= N; ++i) {
      tree.apply(i, i + s, generate<TypeParam>(TestFixture::engine));
    }
  }
  Stop();
  for (int s : sizes) {
    for (int i = 0; i + s <= N; ++i) {
      MEASURE_DUMMY(tree.prod(i, i + s));
    }
  }
}
