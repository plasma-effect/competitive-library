#include "expander.hpp"
#include "get_embedded.hpp"
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
  if (result.inpath.empty() || result.help) {
    std::cerr << "Usage: " << result.execname << "[options] source"
              << std::endl;
    std::cerr << "Options:" << std::endl;
    std::cerr << "  --help, -h  Display this information." << std::endl;
    std::cerr << "  -o <file>   Place the output into <file>." << std::endl;
    return result.inpath.empty() ? EXIT_SUCCESS : EXIT_FAILURE;
  }
  try {
    auto data = source_expander::get_data();
    std::fstream infst(fs::canonical(result.inpath), std::ios::in);
    if (result.outpath.empty()) {
      source_expander::expand(infst, std::cout, data.headers);
    } else {
      std::fstream outfst(fs::weakly_canonical(result.outpath), std::ios::out);
      source_expander::expand(infst, outfst, data.headers);
    }
  } catch (std::exception& e) {
    std::cerr << "ERROR: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
