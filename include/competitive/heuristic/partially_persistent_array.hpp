#pragma once
#include "competitive/utility.hpp"
#include <bits/stdc++.h>

namespace heuristic {
namespace inside {
template <typename T> struct persistent_array_inside {
  using ptr = std::shared_ptr<persistent_array_inside>;
  std::size_t idx, threshold;
  ptr lhs = nullptr, rhs = nullptr;
  T value = {};

  persistent_array_inside(std::size_t min, std::size_t max)
      : idx(min), threshold(std::midpoint(min + 1, max)) {
    CL_ASSERT(min < max);
    if (min + 1 != threshold) {
      lhs = std::make_shared<persistent_array_inside>(min + 1, threshold);
    }
    if (threshold != max) {
      rhs = std::make_shared<persistent_array_inside>(threshold, max);
    }
  }
  template <typename U> ptr update(std::size_t i, U&& u) const {
    auto ret = std::make_shared<persistent_array_inside>(*this);
    if (i == idx) {
      ret->value = std::forward<U>(u);
    } else if (i < threshold) {
      ret->lhs = lhs->update(i, std::forward<U>(u));
    } else {
      ret->rhs = rhs->update(i, std::forward<U>(u));
    }
    return ret;
  }
  T const& get(std::size_t i) const {
    if (i == idx) {
      return value;
    } else if (i < threshold) {
      return lhs->get(i);
    } else {
      return rhs->get(i);
    }
  }
  struct iterator {
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using iterator_concept = std::input_iterator_tag;
    std::size_t idx;
    std::stack<ptr> ptrs;
    iterator& operator++() {
      ++idx;
      if (idx < ptrs.top()->threshold) {
        ptrs.push(ptrs.top()->lhs);
      } else {
        while (ptrs.size()) {
          if (ptrs.top()->rhs && ptrs.top()->rhs->idx == idx) {
            ptrs.push(ptrs.top()->rhs);
            break;
          }
          ptrs.pop();
        }
      }
      return *this;
    }
    iterator operator++(int) {
      auto ret = *this;
      operator++();
      return ret;
    }
    bool operator==(std::default_sentinel_t) const {
      return ptrs.size() == 0;
    }
    const T& operator*() const {
      CL_ASSERT(ptrs.size() > 0);
      return ptrs.top()->value;
    }
  };
};
} // namespace inside
template <std::copy_constructible T> class partially_persistent_array {
  std::shared_ptr<inside::persistent_array_inside<T>> root;
  std::size_t size_;

public:
  partially_persistent_array(std::size_t s)
      : root(std::make_shared<inside::persistent_array_inside<T>>(0, s)),
        size_(s) {}

  void update(std::size_t i, T const& v) {
    root = root->update(i, v);
  }
  T const& get(std::size_t i) const {
    CL_ASSERT(i < size_);
    return root->get(i);
  }
  std::size_t size() const {
    return size_;
  }
  auto begin() const {
    typename inside::persistent_array_inside<T>::iterator ite{};
    ite.ptrs.push(root);
    return ite;
  }
  auto end() const {
    return std::default_sentinel;
  }
};
} // namespace heuristic
