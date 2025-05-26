#pragma once
#include "atcoder/all"
#include "utility.hpp"

namespace common::internal {
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
  ~print_base_t() { ost.flags(base_flags); }

  print_base_t& operator<<(std::string const& str) {
    ost << str;
    return *this;
  }
  print_base_t& operator<<(std::string_view const& view) {
    ost << view;
    return *this;
  }
  print_base_t& operator<<(const char* str) {
    ost << str;
    return *this;
  }
  template <int mod>
  print_base_t& operator<<(atcoder::static_modint<mod> const& val) {
    ost << val.val();
    return *this;
  }
  template <stdstream_able T> print_base_t& operator<<(T const& v) {
    ost << v;
    return *this;
  }
  template <std::input_iterator It> void print_ite(It first, It last) {
    ost << rng_dec.prefix;
    if (first != last) {
      *this << *first;
      for (++first; first != last; ++first) {
        ost << rng_dec.delim;
        *this << *first;
      }
    }
    ost << rng_dec.suffix;
  }
  template <std::ranges::input_range T> print_base_t& operator<<(T const& rng) {
    print_ite(rng.begin(), rng.end());
    return *this;
  }
  template <typename T, std::size_t N>
  print_base_t& operator<<(T const (&ar)[N]) {
    print_ite(std::ranges::begin(ar), std::ranges::end(ar));
    return *this;
  }
  template <std::size_t S, std::size_t I, typename T>
  void tuple_print(T const& t) {
    if constexpr (I == 0) {
      ost << tpl_dec.prefix;
    } else {
      ost << tpl_dec.delim;
    }
    *this << std::get<I>(t);
    if constexpr (I + 1 != S) {
      tuple_print<S, I + 1>(t);
    } else {
      ost << tpl_dec.suffix;
    }
  }
  template <typename T0, typename T1>
  print_base_t& operator<<(std::pair<T0, T1> const& p) {
    tuple_print<2, 0>(p);
    return *this;
  }
  template <typename... Ts>
  print_base_t& operator<<(std::tuple<Ts...> const& t) {
    tuple_print<sizeof...(Ts), 0>(t);
    return *this;
  }
  template <typename T> print_base_t& operator<<(std::optional<T> const& opt) {
    if (opt) {
      *this << *opt;
    } else {
      ost << "<nullopt>";
    }
    return *this;
  }
  template <typename T>
  print_base_t& operator<<(common::dual_array<T> const& ar) {
    auto [H, W] = ar.dimensions();
    const char* outer_delim = "";
    ost << rng_dec.prefix;
    for (auto i : common::irange(H)) {
      ost << std::exchange(outer_delim, rng_dec.delim) << rng_dec.prefix;
      const char* inner_delim = "";
      for (auto j : common::irange(W)) {
        ost << std::exchange(inner_delim, rng_dec.delim);
        *this << ar(i, j);
      }
      ost << rng_dec.suffix;
    }
    ost << rng_dec.suffix;
    return *this;
  }
  print_base_t& operator<<(common::dual_array<bool> const& ar) {
    auto [H, W] = ar.dimensions();
    const char* outer_delim = "";
    ost << rng_dec.prefix;
    for (auto i : common::irange(H)) {
      ost << std::exchange(outer_delim, rng_dec.delim) << rng_dec.prefix;
      const char* inner_delim = "";
      for (auto j : common::irange(W)) {
        ost << std::exchange(inner_delim, rng_dec.delim);
        ost << bool(ar(i, j));
      }
      ost << rng_dec.suffix;
    }
    ost << rng_dec.suffix;
    return *this;
  }
  void set_range_prefix(const char* new_prefix) { rng_dec.prefix = new_prefix; }
  void set_range_suffix(const char* new_suffix) { rng_dec.suffix = new_suffix; }
  void set_range_delim(const char* new_delim) { rng_dec.delim = new_delim; }
  void set_tuple_prefix(const char* new_prefix) { tpl_dec.prefix = new_prefix; }
  void set_tuple_suffix(const char* new_suffix) { tpl_dec.suffix = new_suffix; }
  void set_tuple_delim(const char* new_delim) { tpl_dec.delim = new_delim; }
};

template <typename T>
constexpr bool is_std_manip_v =
    std::is_same_v<T, decltype(std::setbase(std::declval<int>()))> ||
    std::is_same_v<T, decltype(std::setfill(std::declval<char>()))> ||
    std::is_same_v<T, decltype(std::setprecision(std::declval<int>()))> ||
    std::is_same_v<T, decltype(std::setw(std::declval<int>()))> ||
    std::is_convertible_v<T, std::ios_base& (*)(std::ios_base&)>;

template <bool> void print(print_base_t&) {}
template <bool put_blank, typename T, typename... Ts>
void print(print_base_t& pb, T const& arg, Ts const&... args) {
  if constexpr (put_blank) {
    pb << " ";
  }
  pb << arg;
  print<!is_std_manip_v<std::remove_cv_t<T>>>(pb, args...);
}
} // namespace common::internal
