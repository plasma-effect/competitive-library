#include "competitive/algorithm/rolling_hash.hpp"
#include "competitive/heuristic/random.hpp"
#include <measurement.hpp>

static constexpr std::size_t N = 100'000;
using hash_t = algorithm::rolling_hash<'a', 'z'>;

class RollingHashMeasure : public ::measurement::Measure {
  static inline heuristic::xorshift engine;

protected:
  std::uniform_int_distribution<char> dist{'a', 'z'};
  std::string str;
  void SetUp() override {
    str.resize(N);
    for (auto i = 0uz; i < N; ++i) {
      str[i] = dist(engine);
    }
  }
};

MEASURE_F(RollingHashMeasure, CreateHash) {
  Start();
  hash_t hash(str);
  Stop();
  std::size_t count = 0;
  for (auto i = 0uz; i < N; ++i) {
    count += hash == hash.subhash(i);
  }
  MEASURE_DUMMY(count);
}

MEASURE_F(RollingHashMeasure, CreateHashSet) {
  hash_t hash(str);
  std::set<hash_t::subhash_t> hashes;
  Start();
  for (auto i = 0uz; i < N; ++i) {
    hashes.emplace(hash.subhash(i));
  }
  Stop();
  MEASURE_DUMMY(hashes.size());
}

MEASURE_F(RollingHashMeasure, CountEqualSubstr) {
  hash_t hash(str);
  auto target = hash.subhash(0, 1000);
  std::size_t count = 0;
  Start();
  for (auto i = 0uz; i + 1000 <= N; ++i) {
    count += target == hash.subhash(i, 1000);
  }
  Stop();
  MEASURE_DUMMY(count);
}
