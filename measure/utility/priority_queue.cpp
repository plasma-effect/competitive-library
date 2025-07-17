#include "competitive/utility/priority_queue.hpp"
#include "measure_utils.hpp"
#include <measurement.hpp>

namespace {
auto& get_engine() {
  static std::mt19937 engine;
  return engine;
}
int get_first(int v) {
  return v;
}
int get_first(std::pair<int, int> p) {
  return p.first;
}

struct LessMeasureBase {
  static auto make_queue() {
    constexpr auto priority = competitive::priority::less;
    return competitive::make_priority_queue<int>(priority);
  }
  using value_t = int;
  static constexpr const char* p_name = "Less";
};
struct GreaterMeasureBase {
  static auto make_queue() {
    constexpr auto priority = competitive::priority::greater;
    return competitive::make_priority_queue<int>(priority);
  }
  using value_t = int;
  static constexpr const char* p_name = "Greater";
};
struct LessWithProjMeasureBase {
  static auto make_queue() {
    constexpr auto priority = competitive::priority::less;
    return competitive::make_priority_queue<std::pair<int, int>>(
        priority, [](std::pair<int, int> const& p) {
          return std::get<0>(p) + std::get<1>(p);
        });
  }
  using value_t = std::pair<int, int>;
  static constexpr const char* p_name = "LessWithProj";
};
struct GreaterWithProjMeasureBase {
  static auto make_queue() {
    constexpr auto priority = competitive::priority::greater;
    return competitive::make_priority_queue<std::pair<int, int>>(
        priority, [](std::pair<int, int> const& p) {
          return std::get<0>(p) + std::get<1>(p);
        });
  }
  using value_t = std::pair<int, int>;
  static constexpr const char* p_name = "GreaterWithProj";
};
struct SortedCase {
  static void make_vector(std::vector<int>& vec) {
    vec.resize(100'000);
    std::iota(vec.begin(), vec.end(), 0);
  }
  static void make_vector(std::vector<std::pair<int, int>>& vec) {
    vec.resize(100'000);
    for (int i = 0; i < 100'000; ++i) {
      vec.emplace_back(i, 0);
    }
  }
  static constexpr const char* c_name = "Sorted";
};
struct ReversedCase {
  static void make_vector(std::vector<int>& vec) {
    vec.resize(100'000);
    std::iota(vec.begin(), vec.end(), 0);
    std::ranges::reverse(vec);
  }
  static void make_vector(std::vector<std::pair<int, int>>& vec) {
    vec.resize(100'000);
    for (int i = 0; i < 100'000; ++i) {
      vec.emplace_back(-i, 0);
    }
  }
  static constexpr const char* c_name = "Reversed";
};
struct RandomCase {
  static void make_vector(std::vector<int>& vec) {
    vec.resize(100'000);
    std::iota(vec.begin(), vec.end(), 0);
    std::ranges::shuffle(vec, get_engine());
  }
  static void make_vector(std::vector<std::pair<int, int>>& vec) {
    vec.resize(100'000);
    for (int i = 0; i < 100'000; ++i) {
      vec.emplace_back(i, 0);
    }
    std::ranges::shuffle(vec, get_engine());
  }
  static constexpr const char* c_name = "Random";
};

template <typename Priority, typename Case>
struct SuiteTraits : Priority, Case {};
template <typename> struct NameSelectorImpl;
template <typename Priority, typename Cases>
struct NameSelectorImpl<SuiteTraits<Priority, Cases>> {
  static std::string GetName() {
    return std::string(Priority::p_name) + std::string(Cases::c_name);
  }
};
struct NameSelector {
  template <typename T> static std::string GetName(std::size_t) {
    return NameSelectorImpl<T>::GetName();
  }
};
using Priorities =
    ::measurement::Types<LessMeasureBase, GreaterMeasureBase,
                         LessWithProjMeasureBase, GreaterWithProjMeasureBase>;
using Cases = ::measurement::Types<SortedCase, ReversedCase, RandomCase>;
using types =
    typename ::measure_utils::CartesianProductBase<SuiteTraits, Priorities,
                                                   Cases>::type;
} // namespace

template <typename T>
class PriorityQueueMeasure : public ::measurement::Measure {
public:
  std::vector<typename T::value_t> vec;

protected:
  void SetUp() override {
    T::make_vector(vec);
  }
};
TYPED_MEASURE_SUITE(PriorityQueueMeasure, types, NameSelector);

TYPED_MEASURE(PriorityQueueMeasure, Push) {
  auto queue = TypeParam::make_queue();
  int sum = 0;
  Start();
  for (auto v : TestFixture::vec) {
    queue.emplace(v);
  }
  Stop();
  while (queue.size()) {
    sum += get_first(queue.top());
    queue.pop();
  }
  MEASURE_DUMMY(sum);
}

TYPED_MEASURE(PriorityQueueMeasure, Pop) {
  auto queue = TypeParam::make_queue();
  int sum = 0;
  for (auto v : TestFixture::vec) {
    queue.emplace(v);
  }
  Start();
  while (queue.size()) {
    sum += get_first(queue.top());
    queue.pop();
  }
  Stop();
  MEASURE_DUMMY(sum);
}
