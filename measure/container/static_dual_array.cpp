#include "competitive/container/static_dual_array.hpp"
#include "measure_utils.hpp"
#include <measurement.hpp>

using common::static_dual_array;
using measure_utils::add;
using measure_utils::generate;
namespace {
using types = ::measurement::Types<int, double, bool>;
auto& get_engine() {
  static std::mt19937 engine;
  return engine;
}
template <typename T, std::size_t N, std::size_t M>
void make_random_array(static_dual_array<T, N, M>& ar) {
  for (auto i = 0uz; i < N; ++i) {
    for (auto j = 0uz; j < M; ++j) {
      ar(i, j) = generate<T>(get_engine());
    }
  }
}
template <typename T, std::size_t N, std::size_t M>
auto all_sum(static_dual_array<T, N, M> const& ar) {
  T sum{};
  for (auto i = 0uz; i < N; ++i) {
    for (auto j = 0uz; j < M; ++j) {
      sum = add(sum, static_cast<T>(ar(i, j)));
    }
  }
  return sum;
}
template <typename T> constexpr std::size_t get_size() {
  if constexpr (std::is_same_v<T, double>) {
    return 10;
  } else if constexpr (std::is_same_v<T, int>) {
    return 12;
  } else {
    return 14;
  }
}
} // namespace

template <typename T>
class StaticDualArrayMeasure : public ::measurement::Measure {
protected:
  static constexpr int N = 1 << get_size<T>(), M = 1 << 8;
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
TYPED_MEASURE_SUITE(StaticDualArrayMeasure, types,
                    measure_utils::DefaultNameSelector);

TYPED_MEASURE(StaticDualArrayMeasure, AssignByHorizonOrder) {
  static_dual_array<TypeParam, TestFixture::N, TestFixture::M> ar{};
  Start();
  for (int i = 0; i < TestFixture::N; ++i) {
    for (int j = 0; j < TestFixture::M; ++j) {
      ar(i, j) = add(TestFixture::vec0[i], TestFixture::vec1[j]);
    }
  }
  Stop();
  MEASURE_DUMMY(all_sum(ar));
}

TYPED_MEASURE(StaticDualArrayMeasure, AssignByVerticalOrder) {
  static_dual_array<TypeParam, TestFixture::N, TestFixture::M> ar{};
  Start();
  for (int j = 0; j < TestFixture::M; ++j) {
    for (int i = 0; i < TestFixture::N; ++i) {
      ar(i, j) = add(TestFixture::vec0[i], TestFixture::vec1[j]);
    }
  }
  Stop();
  MEASURE_DUMMY(all_sum(ar));
}

TYPED_MEASURE(StaticDualArrayMeasure, AssignByOtherOrder) {
  static_dual_array<TypeParam, TestFixture::N, TestFixture::M> ar{};
  Start();
  for (int idx = 0; idx < 3 * TestFixture::N * TestFixture::M; idx += 3) {
    auto i = (idx >> 8) & (TestFixture::N - 1);
    auto j = idx & (TestFixture::M - 1);
    ar(i, j) = add(TestFixture::vec0[i], TestFixture::vec1[j]);
  }
  Stop();
  MEASURE_DUMMY(all_sum(ar));
}

TYPED_MEASURE(StaticDualArrayMeasure, ReadByHorizonOrder) {
  static_dual_array<TypeParam, TestFixture::N, TestFixture::M> ar{};
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

TYPED_MEASURE(StaticDualArrayMeasure, ReadByVerticalOrder) {
  static_dual_array<TypeParam, TestFixture::N, TestFixture::M> ar{};
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

TYPED_MEASURE(StaticDualArrayMeasure, ReadByOtherOrder) {
  static_dual_array<TypeParam, TestFixture::N, TestFixture::M> ar{};
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
