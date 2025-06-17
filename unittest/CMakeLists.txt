add_library(unittest_utils INTERFACE)
target_include_directories(unittest_utils INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/test_utils
)

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS *.cpp)
add_executable(unittest ${TEST_SOURCES})
target_compile_options(unittest PRIVATE
  -Wall
  -Wextra
  -Wshadow
  -Wconversion
  -Wno-sign-conversion
  -Werror
  -fsanitize=undefined,address
  -fno-sanitize-recover=all
)
target_link_options(unittest PRIVATE
  -fsanitize=undefined,address
)
target_link_libraries(unittest PRIVATE
  competitive
  unittest_utils
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(unittest)
