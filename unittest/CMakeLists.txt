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

# data structure
add_executable(data_structure_min_max_heap_unittest data_structure/min_max_heap.cpp)
apply_common_options(data_structure_min_max_heap_unittest)

# graph algorithm
add_executable(graph_topological_sort_unittest graph/topological_sort.cpp)
apply_common_options(graph_topological_sort_unittest)

add_executable(graph_warshall_floyd_unittest graph/warshall_floyd.cpp)
apply_common_options(graph_warshall_floyd_unittest)

# heuristic utility
add_executable(heuristic_grid_bfs_queue_unittest heuristic/grid_bfs_queue.cpp)
apply_common_options(heuristic_grid_bfs_queue_unittest)

add_executable(heuristic_partially_persistent_array_unittest heuristic/partially_persistent_array.cpp)
apply_common_options(heuristic_partially_persistent_array_unittest)

add_executable(heuristic_random_unittest heuristic/random.cpp)
apply_common_options(heuristic_random_unittest)

add_executable(heuristic_static_container_unittest heuristic/static_container.cpp)
apply_common_options(heuristic_static_container_unittest)

add_executable(heuristic_time_control_unittest heuristic/time_control.cpp)
apply_common_options(heuristic_time_control_unittest)

# common utility
add_executable(utility_assert_unittest utility/assert.cpp)
apply_common_options(utility_assert_unittest)

add_executable(utility_dual_array_unittest utility/dual_array.cpp)
apply_common_options(utility_dual_array_unittest)

add_executable(utility_irange_unittest utility/irange.cpp)
apply_common_options(utility_irange_unittest)

add_executable(utility_priority_queue_unittest utility/priority_queue.cpp)
apply_common_options(utility_priority_queue_unittest)

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

# others
add_executable(math_unittest math.cpp)
apply_common_options(math_unittest)

add_executable(numeric_unittest numeric.cpp)
apply_common_options(numeric_unittest)

add_executable(rolling_hash_unittest rolling_hash.cpp)
apply_common_options(rolling_hash_unittest)

add_executable(segtree_unittest segtree.cpp)
apply_common_options(segtree_unittest)

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS *.cpp)
add_executable(unittest ${TEST_SOURCES})
apply_common_options(unittest ignore)
