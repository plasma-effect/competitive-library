#pragma once
#include <functional>
#include <map>
#include <sstream>

namespace source_expander {
struct embedded_data_t {
  std::map<std::string, std::stringstream> base;
  std::map<std::string, std::reference_wrapper<std::istream>> headers;
};
embedded_data_t get_data();
} // namespace source_expander
