#include "competitive/data_structure/min_max_heap.hpp"
#include <measurement.hpp>

namespace {
auto& get_engine() {
  static std::mt19937 engine;
  return engine;
}
int get_count() {
  static std::uniform_int_distribution<int> dist(1, 10000);
  return dist(get_engine());
}
constexpr int N = 1000'000;
using types = ::measurement::Types<std::vector<int>,
                                   boost::container::static_vector<int, N>>;
struct NameSelector {
  template <typename T> static std::string GetName(std::size_t) {
    if constexpr (std::is_same_v<T, std::vector<int>>) {
      return "std::vector";
    } else {
      return "boost::container::static_vector";
    }
  }
};
} // namespace
template <typename T>
class MinMaxHeapMeasure : public ::measurement::Measure {};
TYPED_MEASURE_SUITE(MinMaxHeapMeasure, types, NameSelector);

TYPED_MEASURE(MinMaxHeapMeasure, PushAscend) {
  competitive::min_max_heap<int, TypeParam> heap;
  Start();
  for (int i = 0; i < N; ++i) {
    heap.push(i);
  }
  Stop();
  for (int c = get_count(); c > 0; --c) {
    heap.pop_min();
  }
  MEASURE_DUMMY(heap.min());
}

TYPED_MEASURE(MinMaxHeapMeasure, PushDescend) {
  competitive::min_max_heap<int, TypeParam> heap;
  Start();
  for (int i = N; i > 0; --i) {
    heap.push(i);
  }
  Stop();
  for (int c = get_count(); c > 0; --c) {
    heap.pop_min();
  }
  MEASURE_DUMMY(heap.min());
}

TYPED_MEASURE(MinMaxHeapMeasure, PushOther) {
  competitive::min_max_heap<int, TypeParam> heap;
  int value = get_count();
  Start();
  for (int i = 0; i < N; ++i) {
    value ^= value << 13;
    value ^= value >> 7;
    value ^= value << 17;
    heap.push(value);
  }
  Stop();
  for (int c = get_count(); c > 0; --c) {
    heap.pop_min();
  }
  MEASURE_DUMMY(heap.min());
}

TYPED_MEASURE(MinMaxHeapMeasure, PopMaxOnly) {
  competitive::min_max_heap<int, TypeParam> heap;
  int value = get_count();
  for (int i = 0; i < N; ++i) {
    value ^= value << 13;
    value ^= value >> 7;
    value ^= value << 17;
    heap.push(value & 0xFFFF);
  }
  int sum = 0;
  Start();
  while (heap.size()) {
    sum += heap.max();
    heap.pop_max();
  }
  Stop();
  MEASURE_DUMMY(sum);
}

TYPED_MEASURE(MinMaxHeapMeasure, PopMinOnly) {
  competitive::min_max_heap<int, TypeParam> heap;
  int value = get_count();
  for (int i = 0; i < N; ++i) {
    value ^= value << 13;
    value ^= value >> 7;
    value ^= value << 17;
    heap.push(value & 0xFFFF);
  }
  int sum = 0;
  Start();
  while (heap.size()) {
    sum += heap.min();
    heap.pop_min();
  }
  Stop();
  MEASURE_DUMMY(sum);
}

TYPED_MEASURE(MinMaxHeapMeasure, PopMutually) {
  competitive::min_max_heap<int, TypeParam> heap;
  int value = get_count();
  for (int i = 0; i < N; ++i) {
    value ^= value << 13;
    value ^= value >> 7;
    value ^= value << 17;
    heap.push(value & 0xFFFF);
  }
  int sum = 0;
  Start();
  while (heap.size()) {
    sum += heap.min() + heap.max();
    heap.pop_min();
    heap.pop_max();
  }
  Stop();
  MEASURE_DUMMY(sum);
}
