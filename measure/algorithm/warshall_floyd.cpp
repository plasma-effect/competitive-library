#include "competitive/algorithm/warshall_floyd.hpp"
#include "measure_utils.hpp"
#include <measurement.hpp>

namespace {
using types = ::measurement::Types<int, std::optional<int>>;
struct NameSelector {
  template <typename T> static std::string GetName(std::size_t) {
    if constexpr (std::is_same_v<T, int>) {
      return "int";
    } else if constexpr (std::is_same_v<T, std::optional<int>>) {
      return "std::optional<int>";
    }
  }
};
constexpr int LARGE = 1000'000'000;
constexpr int N = 1000;
} // namespace

template <typename T>
class WarshallFloydMeasure : public ::measurement::Measure {
  measure_utils::xorshift engine;

protected:
  std::vector<std::map<int, int>> edge;
  void SetUp() override {
    edge.clear();
    edge.resize(N);
    std::uniform_int_distribution<std::size_t> index(0uz, N - 1);
    std::uniform_int_distribution<int> dist(1, 1000);
    atcoder::dsu dsu(N);
    for (int i = 0; i < 2 * N; ++i) {
      std::size_t a, b;
      do {
        a = index(engine);
        b = index(engine);
      } while (a == b || (i < N - 1 && dsu.same(a, b)) ||
               (i >= N - 1 && edge[a].contains(b)));
      edge[a][b] = dist(engine);
    }
  }
};
TYPED_MEASURE_SUITE(WarshallFloydMeasure, types, NameSelector);

TYPED_MEASURE(WarshallFloydMeasure, Execute) {
  common::dual_array<TypeParam> data(N, N);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (TestFixture::edge[i].contains(j)) {
        data(i, j) = TestFixture::edge[i][j];
      } else if constexpr (std::is_same_v<TypeParam, int>) {
        data(i, j) = LARGE;
      }
    }
  }
  Start();
  competitive::warshall_floyd(data);
  Stop();
  if constexpr (std::is_same_v<TypeParam, int>) {
    MEASURE_DUMMY(data(0, 0));
  } else {
    MEASURE_DUMMY(*data(0, 0));
  }
}
