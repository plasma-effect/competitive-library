#include "expander.hpp"
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <set>

int main(int argc, const char* argv[]) {
  namespace fs = std::filesystem;
  auto result = source_expander::parse_argc(argc, argv);
  if (result.inpath.empty()) {
    std::cerr << result.execname << ": fatal error: no source file."
              << std::endl;
  }
  if (result.dirpath.empty() || result.help) {
    std::cerr << "Usage: " << result.execname << "[options] source"
              << std::endl;
    std::cerr << "Options:" << std::endl;
    std::cerr << "  --help, -h  Display this information." << std::endl;
    std::cerr << "  -o <file>   Place the output into <file>." << std::endl;
    std::cerr << "  -d <path>   Specify the library directory." << std::endl;
    return result.dirpath.empty() ? EXIT_SUCCESS : EXIT_FAILURE;
  }
  try {
    std::map<std::string, std::pair<fs::path, std::fstream>> fmap;
    std::map<std::string, std::reference_wrapper<std::istream>> headers;
    for (auto&& r : result.dirpath) {
      auto root = fs::canonical(r);
      for (const auto& p : fs::recursive_directory_iterator(root)) {
        if (p.is_regular_file()) {
          auto relpath = fs::relative(p.path(), root);
          if (fmap.contains(relpath.string())) {
            std::cerr << "ERROR: the name \"" << relpath.string()
                      << " is duplicated." << std::endl;
            std::cerr << "  previously found: "
                      << fs::absolute(fmap[relpath.string()].first)
                      << std::endl;
            std::cerr << "           current: " << fs::absolute(p.path())
                      << std::endl;
            return EXIT_FAILURE;
          }
          auto& [path, fst] = fmap[relpath.string()];
          path = p.path();
          fst.open(path);
          headers.emplace(relpath.string(), source_expander::iref(fst));
        }
      }
    }
    std::fstream infst(fs::canonical(result.inpath), std::ios::in);
    if (result.outpath.empty()) {
      source_expander::expand(infst, std::cout, headers);
    } else {
      std::fstream outfst(fs::weakly_canonical(result.outpath), std::ios::out);
      source_expander::expand(infst, outfst, headers);
    }
  } catch (std::exception& e) {
    std::cerr << "ERROR: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
