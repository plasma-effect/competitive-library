add_library(unittest_utils INTERFACE)
target_include_directories(unittest_utils INTERFACE
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
    unittest_utils
    GTest::gtest_main
  )
  if(COMPETITIVE_BUILD_MODE STREQUAL "Develop")
    target_link_libraries(${target} PRIVATE stdc++exp)
  endif()
  if(${ARGC} EQUAL 1)
    gtest_discover_tests(${target})
  endif()
endfunction()

# container
add_executable(container_dual_array_unittest container/dual_array.cpp)
apply_common_options(container_dual_array_unittest)

add_executable(container_static_dual_array_unittest container/static_dual_array.cpp)
apply_common_options(container_static_dual_array_unittest)

# data structure
add_executable(data_structure_min_max_heap_unittest data_structure/min_max_heap.cpp)
apply_common_options(data_structure_min_max_heap_unittest)

add_executable(data_structure_segtree_unittest data_structure/segtree.cpp)
apply_common_options(data_structure_segtree_unittest)

# algorithm
add_executable(algorithm_rolling_hash_unittest algorithm/rolling_hash.cpp)
apply_common_options(algorithm_rolling_hash_unittest)

add_executable(algorithm_topological_sort_unittest algorithm/topological_sort.cpp)
apply_common_options(algorithm_topological_sort_unittest)

add_executable(algorithm_warshall_floyd_unittest algorithm/warshall_floyd.cpp)
apply_common_options(algorithm_warshall_floyd_unittest)

# heuristic utility
add_executable(heuristic_persistent_array_unittest heuristic/persistent_array.cpp)
apply_common_options(heuristic_persistent_array_unittest)

add_executable(heuristic_random_unittest heuristic/random.cpp)
apply_common_options(heuristic_random_unittest)

add_executable(heuristic_static_container_unittest heuristic/static_container.cpp)
apply_common_options(heuristic_static_container_unittest)

add_executable(heuristic_time_control_unittest heuristic/time_control.cpp)
apply_common_options(heuristic_time_control_unittest)

# common utility
add_executable(utility_assert_unittest utility/assert.cpp)
apply_common_options(utility_assert_unittest)

add_executable(utility_irange_unittest utility/irange.cpp)
apply_common_options(utility_irange_unittest)

add_executable(utility_priority_queue_unittest utility/priority_queue.cpp)
apply_common_options(utility_priority_queue_unittest)

# math
add_executable(math_factorial_unittest math/factorial.cpp)
apply_common_options(math_factorial_unittest)

add_executable(math_monoid_unittest math/monoid.cpp)
apply_common_options(math_monoid_unittest)

# stdin/stdout
add_executable(io_debug_print_unittest io/debug_print.cpp)
apply_common_options(io_debug_print_unittest)

add_executable(io_normal_print_unittest io/normal_print.cpp)
apply_common_options(io_normal_print_unittest)

add_executable(io_print_base_unittest io/print_base.cpp)
apply_common_options(io_print_base_unittest)

# union headers
add_executable(stdio_unittest stdio.cpp)
apply_common_options(stdio_unittest)

add_executable(utility_unittest utility.cpp)
apply_common_options(utility_unittest)

add_executable(heuristic_unittest heuristic.cpp)
apply_common_options(heuristic_unittest)

add_executable(math_unittest math.cpp)
apply_common_options(math_unittest)

# link all
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS *.cpp)
add_executable(unittest ${TEST_SOURCES})
apply_common_options(unittest ignore)
