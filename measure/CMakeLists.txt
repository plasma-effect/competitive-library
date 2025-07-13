add_library(measure_utils INTERFACE)
target_include_directories(measure_utils INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/measure_utils
)
target_link_libraries(measure_utils INTERFACE measurement)

file(GLOB_RECURSE MEASURE_SOURCES CONFIGURE_DEPENDS *.cpp)
add_executable(measure_test ${MEASURE_SOURCES})
target_compile_options(measure_test PRIVATE
  -Wall
  -Wextra
  -Wshadow
  -Wno-sign-conversion
  -Werror
  -O3
)
target_link_libraries(measure_test PRIVATE 
  competitive 
  measure_utils
  measurement
)
if(COMPETITIVE_BUILD_MODE STREQUAL "Develop")
  target_link_libraries(measure_test PRIVATE stdc++exp)
endif()
