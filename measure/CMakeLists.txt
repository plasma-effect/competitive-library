add_library(measure_utils INTERFACE)
target_include_directories(measure_utils INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/measure_utils
)
target_link_libraries(measure_utils INTERFACE measurement)

function(apply_common_options target)
  target_compile_options(${target} PRIVATE
    -Wall
    -Wextra
    -Wshadow
    -Wno-sign-conversion
    -Werror
    -O3
  )
  target_link_libraries(${target} PRIVATE 
    competitive 
    measure_utils
    measurement
  )
  if(COMPETITIVE_BUILD_MODE STREQUAL "Develop")
    target_link_libraries(${target} PRIVATE stdc++exp)
  endif()
endfunction()

# container
add_executable(container_dual_array_measure container/dual_array.cpp)
apply_common_options(container_dual_array_measure)

add_executable(container_static_dual_array_measure container/static_dual_array.cpp)
apply_common_options(container_static_dual_array_measure)

# data structure
add_executable(data_structure_min_max_heap_measure data_structure/min_max_heap.cpp)
apply_common_options(data_structure_min_max_heap_measure)

add_executable(data_structure_segtree_measure data_structure/segtree.cpp)
apply_common_options(data_structure_segtree_measure)

# algorithm
add_executable(algorithm_rolling_hash_measure algorithm/rolling_hash.cpp)
apply_common_options(algorithm_rolling_hash_measure)

add_executable(algorithm_topological_sort_measure algorithm/topological_sort.cpp)
apply_common_options(algorithm_topological_sort_measure)

add_executable(algorithm_warshall_floyd_measure algorithm/warshall_floyd.cpp)
apply_common_options(algorithm_warshall_floyd_measure)

# heuristic utility
add_executable(heuristic_persistent_array_measure heuristic/persistent_array.cpp)
apply_common_options(heuristic_persistent_array_measure)

add_executable(heuristic_random_measure heuristic/random.cpp)
apply_common_options(heuristic_random_measure)

# add_executable(heuristic_static_container_measure heuristic/static_container.cpp)
# apply_common_options(heuristic_static_container_measure)

add_executable(heuristic_time_control_measure heuristic/time_control.cpp)
apply_common_options(heuristic_time_control_measure)

# common utility
# add_executable(utility_assert_measure utility/assert.cpp)
# apply_common_options(utility_assert_measure)

# add_executable(utility_irange_measure utility/irange.cpp)
# apply_common_options(utility_irange_measure)

add_executable(utility_priority_queue_measure utility/priority_queue.cpp)
apply_common_options(utility_priority_queue_measure)

# math
# add_executable(math_factorial_measure math/factorial.cpp)
# apply_common_options(math_factorial_measure)

# add_executable(math_monoid_measure math/monoid.cpp)
# apply_common_options(math_monoid_measure)

# stdin/stdout
# add_executable(io_debug_print_measure io/debug_print.cpp)
# apply_common_options(io_debug_print_measure)

# add_executable(io_normal_print_measure io/normal_print.cpp)
# apply_common_options(io_normal_print_measure)

# add_executable(io_print_base_measure io/print_base.cpp)
# apply_common_options(io_print_base_measure)

# union headers
# add_executable(stdio_measure stdio.cpp)
# apply_common_options(stdio_measure)

# add_executable(utility_measure utility.cpp)
# apply_common_options(utility_measure)

# add_executable(heuristic_measure heuristic.cpp)
# apply_common_options(heuristic_measure)

# add_executable(math_measure math.cpp)
# apply_common_options(math_measure)
