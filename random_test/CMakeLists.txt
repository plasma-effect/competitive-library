add_library(random_test_utils INTERFACE)
target_include_directories(random_test_utils INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/test_utils
)

function(apply_common_options)
  set(target ${ARGV0})
  target_compile_options(${target} PRIVATE
    -Wall
    -Wextra
    -Wshadow
    -Wconversion
    -Wno-sign-conversion
    -Werror
    -fsanitize=undefined,address
    -fno-sanitize-recover=all
  )
  target_link_options(${target} PRIVATE
    -fsanitize=undefined,address
  )
  target_link_libraries(${target} PRIVATE
    competitive
    random_test_utils
    GTest::gtest_main
  )
  if(COMPETITIVE_BUILD_MODE STREQUAL "Develop")
    target_link_libraries(${target} PRIVATE stdc++exp)
  endif()
  if(${ARGC} EQUAL 1)
    gtest_discover_tests(${target})
  endif()
endfunction()

add_executable(data_structure_min_max_heap_random_test data_structure/min_max_heap.cpp)
apply_common_options(data_structure_min_max_heap_random_test)

add_executable(algorithm_rolling_hash_random_test algorithm/rolling_hash.cpp)
apply_common_options(algorithm_rolling_hash_random_test)

add_executable(algorithm_topological_sort_random_test algorithm/topological_sort.cpp)
apply_common_options(algorithm_topological_sort_random_test)

add_executable(heuristic_persistent_array_random_test heuristic/persistent_array.cpp)
apply_common_options(heuristic_persistent_array_random_test)

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS *.cpp)
add_executable(random_test ${TEST_SOURCES})
apply_common_options(random_test "ignore")

