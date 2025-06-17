add_library(unittest_utils INTERFACE)
target_include_directories(unittest_utils INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/test_utils
)

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS *.cpp)
add_executable(unittest ${TEST_SOURCES})
target_link_libraries(unittest PRIVATE
  competitive
  unittest_utils
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(unittest)
