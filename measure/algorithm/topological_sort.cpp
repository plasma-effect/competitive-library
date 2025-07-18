#include "competitive/algorithm/topological_sort.hpp"
#include "atcoder/dsu.hpp"
#include "measure_utils.hpp"

constexpr std::size_t N = 100'000;
MEASURE(TopologicalSortMeasure, NonCycleGraph) {
  static measure_utils::xorshift engine;
  std::uniform_int_distribution<std::size_t> dist(0uz, N - 1);
  std::vector<std::size_t> order(N);
  std::iota(order.begin(), order.end(), 0uz);
  std::ranges::shuffle(order, engine);
  std::vector<std::set<int>> edge(N);
  atcoder::dsu dsu(N);
  for (auto i = 0uz; i < N - 1; ++i) {
    std::size_t a, b;
    do {
      a = dist(engine);
      b = dist(engine);
    } while (dsu.same(a, b));
    if (order[a] > order[b]) {
      std::swap(a, b);
    }
    edge[a].emplace(b);
  }
  for (auto i = N - 1; i < 2 * N; ++i) {
    std::size_t a, b;
    do {
      a = dist(engine);
      b = dist(engine);
      if (order[a] > order[b]) {
        std::swap(a, b);
      }
    } while (a == b || edge[a].contains(b));
    edge[a].emplace(b);
  }
  Start();
  auto result = competitive::topological_sort(edge);
  Stop();
  MEASURE_DUMMY(static_cast<bool>(result));
}
