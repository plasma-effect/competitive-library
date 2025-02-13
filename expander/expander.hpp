#pragma once
#include <filesystem>
#include <functional>
#include <istream>
#include <map>
#include <ostream>

namespace source_expander {
inline std::reference_wrapper<std::istream> iref(std::istream& ist) {
  return std::ref(ist);
}
void expand(
    std::istream& ist, std::ostream& ost,
    std::map<std::string, std::reference_wrapper<std::istream>> const& headers);
struct parse_result_t {
  const char* execname;
  std::filesystem::path inpath;
  std::filesystem::path outpath;
  std::vector<std::filesystem::path> dirpath;
  bool help;
};
parse_result_t parse_argc(int argc, const char* argv[]);
} // namespace source_expander
