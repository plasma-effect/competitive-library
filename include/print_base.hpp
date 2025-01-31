#pragma once
#include "atcoder/modint.hpp"
#include "utility.hpp"

namespace atcoder {
template <int mod>
std::ostream& operator<<(std::ostream& ost, static_modint<mod> const& val) {
  return ost << val.val();
}
} // namespace atcoder
namespace print_detail {
template <typename T>
concept stdstream_able = requires(T a) { std::declval<std::ostream&>() << a; };

class print_base_t {
  std::ios_base::fmtflags base_flags;
  std::ostream& ost;
  struct dec_t {
    const char* prefix = "";
    const char* suffix = "";
    const char* delim = " ";
  };
  dec_t rng_dec, tpl_dec;

public:
  print_base_t(std::ostream& os)
      : base_flags(os.flags()), ost(os), rng_dec{}, tpl_dec{} {}
  ~print_base_t() { ost.setf(base_flags); }

  void print(std::string const& str) { ost << str; }
  void print(std::string_view const& view) { ost << view; }
  void print(const char* str) { ost << str; }
  template <stdstream_able T> void print(T const& v) { ost << v; }
  template <std::input_iterator It> void print(It first, It last) {
    ost << rng_dec.prefix;
    if (first != last) {
      print(*first);
      for (++first; first != last; ++first) {
        ost << rng_dec.delim;
        print(*first);
      }
    }
    ost << rng_dec.suffix;
  }
  template <std::integral Int>
  void print(common::integer_range<Int> const& rng) {
    print(rng.begin(), rng.end());
  }
  template <std::ranges::input_range T> void print(T const& rng) {
    print(rng.begin(), rng.end());
  }
  template <typename T, std::size_t N> void print(T const (&ar)[N]) {
    print(std::ranges::begin(ar), std::ranges::end(ar));
  }
  template <std::size_t S, std::size_t I, typename T>
  void tuple_print(T const& t) {
    if constexpr (I == 0) {
      ost << tpl_dec.prefix;
    } else {
      ost << tpl_dec.delim;
    }
    print(std::get<I>(t));
    if constexpr (I + 1 != S) {
      tuple_print<S, I + 1>(t);
    } else {
      ost << tpl_dec.suffix;
    }
  }
  template <typename T0, typename T1> void print(std::pair<T0, T1> const& p) {
    tuple_print<2, 0>(p);
  }
  template <typename... Ts> void print(std::tuple<Ts...> const& t) {
    tuple_print<sizeof...(Ts), 0>(t);
  }
  void set_range_prefix(const char* new_prefix) { rng_dec.prefix = new_prefix; }
  void set_range_suffix(const char* new_suffix) { rng_dec.suffix = new_suffix; }
  void set_range_delim(const char* new_delim) { rng_dec.delim = new_delim; }
  void set_tuple_prefix(const char* new_prefix) { tpl_dec.prefix = new_prefix; }
  void set_tuple_suffix(const char* new_suffix) { tpl_dec.suffix = new_suffix; }
  void set_tuple_delim(const char* new_delim) { tpl_dec.delim = new_delim; }
};
} // namespace print_detail
