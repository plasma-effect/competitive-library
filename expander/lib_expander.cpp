#include "expander.hpp"
#include <cstring>
#include <iostream>
#include <regex>
#include <set>
#include <string>
#include <string_view>

namespace {
void expand_impl(
    std::istream& ist, std::ostream& ost,
    std::map<std::string, std::reference_wrapper<std::istream>> const& headers,
    std::set<std::string>& included, bool in_header) {
  std::string line;
  std::smatch match;
  while (std::getline(ist, line)) {
    if (std::regex_search(line, match, std::regex("^#pragma once"))) {
      continue;
    } else if (std::regex_search(line, match,
                                 std::regex("^#include \"([^\"]*?)\"")) ||
               std::regex_search(line, match,
                                 std::regex("^#include <([^>]*?)>"))) {
      if (!included.contains(match[1])) {
        included.emplace(match[1]);
        if (headers.contains(match[1])) {
          expand_impl(headers.at(match[1]), ost, headers, included, true);
        } else {
          ost << line << std::endl;
        }
      }
    } else if (!in_header || line != "") {
      ost << line << std::endl;
    }
  }
}

source_expander::parse_result_t parse_argc_impl(int argc, const char* argv[]) {
  namespace fs = std::filesystem;
  using namespace std::string_view_literals;

  source_expander::parse_result_t result{};
  result.execname = argv[0];
  for (int i = 1; i < argc; ++i) {
    if (argv[i] == "--help"sv || argv[i] == "-h"sv) {
      result.help = true;
    } else if (argv[i] == "-o"sv) {
      if (!result.outpath.empty()) {
        throw std::runtime_error(
            "the '-o' option was specified multiple times.");
      } else if (i + 1 >= argc) {
        throw std::runtime_error(
            "no filename is specified after the '-o' option.");
      } else {
        result.outpath = argv[++i];
      }
    } else if (!result.inpath.empty()) {
      throw std::runtime_error("the <file> has been specified multiple times.");
    } else {
      result.inpath = argv[i];
    }
  }
  return result;
}

} // namespace

namespace source_expander {
void expand(std::istream& ist, std::ostream& ost,
            std::map<std::string, std::reference_wrapper<std::istream>> const&
                headers) {
  std::set<std::string> included;
  expand_impl(ist, ost, headers, included, false);
}
parse_result_t parse_argc(int argv, const char* argc[]) {
  return parse_argc_impl(argv, argc);
}

} // namespace source_expander
