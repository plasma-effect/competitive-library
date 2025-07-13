#include "competitive/container/dual_array.hpp"
#include "measure_utils.hpp"
#include <measurement.hpp>

using competitive::container::dual_array;
using measure_utils::add;
using measure_utils::generate;
namespace {
using types = ::measurement::Types<int, double, bool>;
auto& get_engine() {
  static std::mt19937 engine;
  return engine;
}
template <typename T> void make_random_array(dual_array<T>& ar) {
  auto [N, M] = ar.dimensions();
  for (auto i = 0uz; i < N; ++i) {
    for (auto j = 0uz; j < M; ++j) {
      ar(i, j) = generate<T>(get_engine());
    }
  }
}
template <typename T> auto all_sum(dual_array<T> const& ar) {
  T sum{};
  auto [N, M] = ar.dimensions();
  for (auto i = 0uz; i < N; ++i) {
    for (auto j = 0uz; j < M; ++j) {
      sum = add(sum, static_cast<T>(ar(i, j)));
    }
  }
  return sum;
}
} // namespace

template <typename T> class DualArrayMeasure : public ::measurement::Measure {
protected:
  static constexpr int N = 1 << (std::is_same_v<T, double> ? 10 : 12),
                       M = 1 << 8;
  std::array<T, N> vec0{};
  std::array<T, M> vec1{};

  void SetUp() override {
    auto& engine = get_engine();
    for (auto& v : vec0) {
      v = generate<T>(engine);
    }
    for (auto& v : vec1) {
      v = generate<T>(engine);
    }
  }
};
TYPED_MEASURE_SUITE(DualArrayMeasure, types,
                    measure_utils::DefaultNameSelector);

TYPED_MEASURE(DualArrayMeasure, AssignByHorizonOrder) {
  dual_array<TypeParam> ar(TestFixture::N, TestFixture::M);
  Start();
  for (int i = 0; i < TestFixture::N; ++i) {
    for (int j = 0; j < TestFixture::M; ++j) {
      ar(i, j) = add(TestFixture::vec0[i], TestFixture::vec1[j]);
    }
  }
  Stop();
  MEASURE_DUMMY(all_sum(ar));
}

TYPED_MEASURE(DualArrayMeasure, AssignByVerticalOrder) {
  dual_array<TypeParam> ar(TestFixture::N, TestFixture::M);
  Start();
  for (int j = 0; j < TestFixture::M; ++j) {
    for (int i = 0; i < TestFixture::N; ++i) {
      ar(i, j) = add(TestFixture::vec0[i], TestFixture::vec1[j]);
    }
  }
  Stop();
  MEASURE_DUMMY(all_sum(ar));
}

TYPED_MEASURE(DualArrayMeasure, AssignByOtherOrder) {
  dual_array<TypeParam> ar(TestFixture::N, TestFixture::M);
  Start();
  for (int idx = 0; idx < 3 * TestFixture::N * TestFixture::M; idx += 3) {
    auto i = (idx >> 8) & (TestFixture::N - 1);
    auto j = idx & (TestFixture::M - 1);
    ar(i, j) = add(TestFixture::vec0[i], TestFixture::vec1[j]);
  }
  Stop();
  MEASURE_DUMMY(all_sum(ar));
}

TYPED_MEASURE(DualArrayMeasure, ReadByHorizonOrder) {
  dual_array<TypeParam> ar(TestFixture::N, TestFixture::M);
  make_random_array(ar);
  TypeParam sum{};
  Start();
  for (int i = 0; i < TestFixture::N; ++i) {
    for (int j = 0; j < TestFixture::M; ++j) {
      sum = add(sum, static_cast<TypeParam>(ar(i, j)));
    }
  }
  Stop();
  MEASURE_DUMMY(sum);
}

TYPED_MEASURE(DualArrayMeasure, ReadByVerticalOrder) {
  dual_array<TypeParam> ar(TestFixture::N, TestFixture::M);
  make_random_array(ar);
  TypeParam sum{};
  Start();
  for (int j = 0; j < TestFixture::M; ++j) {
    for (int i = 0; i < TestFixture::N; ++i) {
      sum = add(sum, static_cast<TypeParam>(ar(i, j)));
    }
  }
  Stop();
  MEASURE_DUMMY(sum);
}

TYPED_MEASURE(DualArrayMeasure, ReadByOtherOrder) {
  dual_array<TypeParam> ar(TestFixture::N, TestFixture::M);
  make_random_array(ar);
  Start();
  TypeParam sum{};
  for (int idx = 0; idx < 3 * TestFixture::N * TestFixture::M; idx += 3) {
    auto i = (idx >> 8) & (TestFixture::N - 1);
    auto j = idx & (TestFixture::M - 1);
    sum = add(sum, static_cast<TypeParam>(ar(i, j)));
  }
  Stop();
  MEASURE_DUMMY(sum);
}
