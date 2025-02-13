#include "expander.hpp"
#include "gtest/gtest.h"
#include <sstream>

class ExpanderTest : public ::testing::Test {
protected:
  std::stringstream base;
  virtual void SetUp() {
    base << "#include <iostream>" << std::endl;
    base << "#include \"test0.hpp\"" << std::endl;
    base << "#include <test1.hpp>" << std::endl;
    base << "#include \"subdir/test2.hpp\"" << std::endl;
    base << std::endl;
    base << "void Main() {}" << std::endl;
  }
};

TEST_F(ExpanderTest, IncludeDoubleQuotation) {
  std::stringstream test0, output;
  test0 << "constexpr int value = 0;" << std::endl;
  std::map<std::string, std::reference_wrapper<std::istream>> headers = {
      {"test0.hpp", source_expander::iref(test0)},
  };
  source_expander::expand(base, output, headers);
  ASSERT_EQ(output.str(), R"(#include <iostream>
#include <test1.hpp>
#include "subdir/test2.hpp"
constexpr int value = 0;

void Main() {}
)");
}

TEST_F(ExpanderTest, IncludeInequalitySign) {
  std::stringstream test1, output;
  test1 << "constexpr int value = 0;" << std::endl;
  std::map<std::string, std::reference_wrapper<std::istream>> headers = {
      {"test1.hpp", source_expander::iref(test1)},
  };
  source_expander::expand(base, output, headers);
  ASSERT_EQ(output.str(), R"(#include <iostream>
#include "test0.hpp"
#include "subdir/test2.hpp"
constexpr int value = 0;

void Main() {}
)");
}

TEST_F(ExpanderTest, IncludeSubdir) {
  std::stringstream test2, output;
  test2 << "constexpr int value = 0;" << std::endl;
  std::map<std::string, std::reference_wrapper<std::istream>> headers = {
      {"subdir/test2.hpp", source_expander::iref(test2)},
  };
  source_expander::expand(base, output, headers);
  ASSERT_EQ(output.str(), R"(#include <iostream>
#include "test0.hpp"
#include <test1.hpp>
constexpr int value = 0;

void Main() {}
)");
}

TEST_F(ExpanderTest, IgnoreIncludeGuard) {
  std::stringstream test0;
  test0 << "#pragma once" << std::endl;
  test0 << "constexpr int value = 0;" << std::endl;
  std::stringstream test1;
  test1 << "#pragma once // include guard" << std::endl;
  test1 << "constexpr double pi = 3.1415926535;" << std::endl;
  std::map<std::string, std::reference_wrapper<std::istream>> headers = {
      {"test0.hpp", source_expander::iref(test0)},
      {"test1.hpp", source_expander::iref(test1)},
  };
  std::stringstream output;
  source_expander::expand(base, output, headers);
  ASSERT_EQ(output.str(), R"(#include <iostream>
#include "subdir/test2.hpp"
constexpr int value = 0;
constexpr double pi = 3.1415926535;

void Main() {}
)");
}

TEST_F(ExpanderTest, RecursiveInclude) {
  std::stringstream test0;
  test0 << "#pragma once" << std::endl;
  test0 << "constexpr int value = 0;" << std::endl;
  std::stringstream test1;
  test1 << "#pragma once" << std::endl;
  test1 << "#include <test0.hpp>" << std::endl;
  test1 << "constexpr double pi = 3.1415926535;" << std::endl;
  std::map<std::string, std::reference_wrapper<std::istream>> headers = {
      {"test0.hpp", source_expander::iref(test0)},
      {"test1.hpp", source_expander::iref(test1)},
  };
  std::stringstream output;
  source_expander::expand(base, output, headers);
  ASSERT_EQ(output.str(), R"(#include <iostream>
#include "subdir/test2.hpp"
constexpr int value = 0;
constexpr double pi = 3.1415926535;

void Main() {}
)");
}

TEST_F(ExpanderTest, AggregateHeaders) {
  std::stringstream test0;
  test0 << "#pragma once" << std::endl;
  test0 << "#include <limits>" << std::endl;
  test0 << "constexpr int value = std::numeric_limits<int>::max();"
        << std::endl;
  std::stringstream test1;
  test1 << "#pragma once" << std::endl;
  test1 << "#include <cmath>" << std::endl;
  test1 << "constexpr double e = std::exp(1.0);" << std::endl;
  std::map<std::string, std::reference_wrapper<std::istream>> headers = {
      {"test0.hpp", source_expander::iref(test0)},
      {"test1.hpp", source_expander::iref(test1)},
  };
  std::stringstream output;
  source_expander::expand(base, output, headers);
  ASSERT_EQ(output.str(), R"(#include <iostream>
#include <limits>
#include <cmath>
#include "subdir/test2.hpp"
constexpr int value = std::numeric_limits<int>::max();
constexpr double e = std::exp(1.0);

void Main() {}
)");
}

TEST_F(ExpanderTest, RemoveDuplicatedHeader) {
  std::stringstream test0;
  test0 << "#pragma once" << std::endl;
  test0 << "#include <bits/stdc++.h>" << std::endl;
  test0 << "constexpr int value = std::numeric_limits<int>::max();"
        << std::endl;
  std::stringstream test1;
  test1 << "#pragma once" << std::endl;
  test1 << "#include <bits/stdc++.h>" << std::endl;
  test1 << "constexpr double e = std::exp(1.0);" << std::endl;
  std::map<std::string, std::reference_wrapper<std::istream>> headers = {
      {"test0.hpp", source_expander::iref(test0)},
      {"test1.hpp", source_expander::iref(test1)},
  };
  std::stringstream output;
  source_expander::expand(base, output, headers);
  ASSERT_EQ(output.str(), R"(#include <iostream>
#include <bits/stdc++.h>
#include "subdir/test2.hpp"
constexpr int value = std::numeric_limits<int>::max();
constexpr double e = std::exp(1.0);

void Main() {}
)");
}

TEST(ParseArgs, ParseArgs) {
  const char* argv[] = {"unittest", "in.cpp", "-o",
                        "out.cpp",  "-d",     "include/"};
  auto result = source_expander::parse_argc(6, argv);
  EXPECT_EQ(result.inpath.string(), "in.cpp");
  EXPECT_EQ(result.outpath.string(), "out.cpp");

  ASSERT_EQ(result.dirpath.size(), 1);
  EXPECT_EQ(result.dirpath[0], "include/");
}

TEST(ParseArgs, ParseHelp) {
  const char* argv[] = {"unittest", "--help"};
  auto result = source_expander::parse_argc(2, argv);
  ASSERT_TRUE(result.help);
}

TEST(ParseArgs, ParseHelpShort) {
  const char* argv[] = {"unittest", "-h"};
  auto result = source_expander::parse_argc(2, argv);
  ASSERT_TRUE(result.help);
}

TEST(ParseArgs, GiveSourceTwice) {
  const char* argv[] = {"unittest", "in.cpp", "source.cpp"};
  EXPECT_THROW(source_expander::parse_argc(3, argv), std::runtime_error);
}

TEST(ParseArgs, GiveOutputTwice) {
  const char* argv[] = {"unittest", "-o", "out0.cpp", "-o", "out1.cpp"};
  EXPECT_THROW(source_expander::parse_argc(5, argv), std::runtime_error);
}

TEST(ParseArgs, GiveDirTwice) {
  const char* argv[] = {"unittest", "-d", "include/", "-d", "sub/"};
  auto result = source_expander::parse_argc(5, argv);
  ASSERT_EQ(result.dirpath.size(), 2);
  EXPECT_EQ(result.dirpath[0].string(), "include/");
  EXPECT_EQ(result.dirpath[1].string(), "sub/");
}

TEST(ParseArgs, GiveOutputNone) {
  const char* argv[] = {"unittest", "-o"};
  EXPECT_THROW(source_expander::parse_argc(2, argv), std::runtime_error);
}

TEST(ParseArgs, GiveDirNone) {
  const char* argv[] = {"unittest", "-d"};
  EXPECT_THROW(source_expander::parse_argc(2, argv), std::runtime_error);
}

TEST(ParseArgs, GiveHelpAsOutput) {
  const char* argv[] = {"unittest", "-o", "--help"};
  auto result = source_expander::parse_argc(3, argv);
  EXPECT_EQ(result.outpath.string(), "--help");
}
