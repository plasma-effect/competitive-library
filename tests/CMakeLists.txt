cmake_minimum_required(VERSION 3.17)

cmake_policy(SET CMP0048 NEW)
project(CompetitiveLibrary)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wshadow -Wconversion -Wno-sign-conversion -Werror)
add_compile_options(-fsanitize=undefined,address -fno-sanitize-recover=all)
add_link_options(-fsanitize=undefined,address)

enable_testing()

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include(GoogleTest)

include_directories(../include)
include_directories(../custom-ac-library)
include_directories($ENV{HOME}/boost_1_82_0/include)

add_executable(test_all
  utility.cpp
  print_base.cpp)
target_link_libraries(test_all gtest gtest_main)
gtest_discover_tests(test_all)
