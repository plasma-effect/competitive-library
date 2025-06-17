set(EMBEDDED_HEADERS_CPP "${CMAKE_BINARY_DIR}/embedded_headers.cpp")
add_custom_command(
    OUTPUT ${EMBEDDED_HEADERS_CPP}
    COMMAND ${CMAKE_CURRENT_LIST_DIR}/generate_embedded_headers.sh > ${EMBEDDED_HEADERS_CPP}
)

add_library(lib_expander lib_expander.cpp)
target_include_directories(lib_expander PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_library(lib_embedded_headers ${EMBEDDED_HEADERS_CPP})
target_include_directories(lib_embedded_headers PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_executable(expander expander.cpp)
target_link_libraries(expander PRIVATE
  lib_expander
  lib_embedded_headers
)
target_compile_options(expander PRIVATE -Wall -Wextra -Wshadow -Wconversion -Werror)

add_executable(test_expander test_expander.cpp)
target_link_libraries(test_expander PRIVATE
  lib_expander
  GTest::gtest_main
)
target_compile_options(test_expander PRIVATE
  -Wall
  -Wextra
  -Wshadow
  -Wconversion
  -Werror
  -fsanitize=undefined,address
  -fno-sanitize-recover=all
)
target_link_options(test_expander PRIVATE
  -fsanitize=undefined,address
)
include(GoogleTest)
gtest_discover_tests(test_expander)
