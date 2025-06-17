add_library(random_test_utils INTERFACE)
target_include_directories(random_test_utils INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/test_utils
)

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS *.cpp)
add_executable(random_test ${TEST_SOURCES})
target_compile_options(random_test PRIVATE
  -Wall
  -Wextra
  -Wshadow
  -Wconversion
  -Wno-sign-conversion
  -Werror
  -fsanitize=undefined,address
  -fno-sanitize-recover=all
)
target_link_options(random_test PRIVATE
  -fsanitize=undefined,address
)
target_link_libraries(random_test PRIVATE
  competitive
  random_test_utils
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(random_test)
