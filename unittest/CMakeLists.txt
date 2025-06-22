add_library(unittest_utils INTERFACE)
target_include_directories(unittest_utils INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/test_utils
)

function(check_test_exists)
  file(GLOB_RECURSE ALL_HEADERS "${CMAKE_SOURCE_DIR}/include/*.hpp")
  set(MISSING_TESTS "")
  foreach(header IN LISTS ALL_HEADERS)
    file(RELATIVE_PATH rel_path ${CMAKE_SOURCE_DIR}/include ${header})
    string(REPLACE ".hpp" ".cpp" test_path ${rel_path})
    set(full_test_path ${CMAKE_SOURCE_DIR}/unittest/${test_path})
    
    if(NOT EXISTS ${full_test_path})
      list(APPEND MISSING_TESTS ${rel_path})
    endif()
  endforeach()

  if(MISSING_TESTS)
    message(FATAL_ERROR "Missing test files: ${MISSING_TESTS}")
  endif()
endfunction()
check_test_exists()

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
if(COMPETITIVE_BUILD_MODE STREQUAL "Develop")
target_link_libraries(unittest PRIVATE competitive stdc++exp)
endif()

include(GoogleTest)
gtest_discover_tests(unittest)
