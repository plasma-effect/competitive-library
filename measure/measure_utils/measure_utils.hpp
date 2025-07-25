#pragma once
#include <measurement.hpp>
#include <type_traits>

namespace measure_utils {
template <template <typename, typename> typename T, typename, typename>
struct CartesianProductBase;
template <template <typename, typename> typename T, typename T0,
          typename... Ts0, typename... Ts1>
struct CartesianProductBase<T, ::measurement::Types<T0, Ts0...>,
                            ::measurement::Types<Ts1...>> {
  using type = ::measurement::ConcatTypeList<
      ::measurement::Types<T<T0, Ts1>...>,
      typename CartesianProductBase<T, ::measurement::Types<Ts0...>,
                                    ::measurement::Types<Ts1...>>::type>;
};
template <template <typename, typename> typename T, typename... Ts1>
struct CartesianProductBase<T, ::measurement::Types<>,
                            ::measurement::Types<Ts1...>> {
  using type = ::measurement::Types<>;
};

template <typename T> auto add(T const& a, T const& b) {
  if constexpr (std::is_same_v<T, bool>) {
    return a ^ b;
  } else {
    return a + b;
  }
}
template <typename T, typename Engine> auto generate(Engine& engine) {
  if constexpr (std::is_same_v<T, bool>) {
    return engine() % 2 == 0;
  } else if constexpr (std::is_integral_v<T>) {
    static std::uniform_int_distribution<T> dist(0, 15);
    return dist(engine);
  } else if constexpr (std::is_floating_point_v<T>) {
    constexpr int digits = std::numeric_limits<T>::digits;
    return std::generate_canonical<T, digits>(engine);
  }
}
struct xorshift {
  std::uint64_t state;
  xorshift(std::uint64_t seed = 1) : state(seed) {}
  std::uint64_t operator()() {
    state ^= state << 13;
    state ^= state >> 7;
    state ^= state << 17;
    return state ^ (state >> 32);
  }
  using result_type = std::uint64_t;
  static constexpr std::uint64_t min() {
    return 1;
  }
  static constexpr std::uint64_t max() {
    return std::numeric_limits<std::uint64_t>::max();
  }
};
struct DefaultNameSelector {
  template <typename T> static std::string GetName(std::size_t) {
    if constexpr (std::is_same_v<T, int>) {
      return "int";
    } else if constexpr (std::is_same_v<T, double>) {
      return "double";
    } else if constexpr (std::is_same_v<T, bool>) {
      return "bool";
    }
  }
};
} // namespace measure_utils
