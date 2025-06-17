cmake_minimum_required(VERSION 3.16)
project(CompetitiveLibrary LANGUAGES CXX)

set(HOME_DIR $ENV{HOME})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(competitive INTERFACE)
target_include_directories(competitive INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/ac-library/custom
  ${HOME_DIR}/boost_1_82_0/include
)

enable_testing()
include(FetchContent)
FetchContent_Declare(
  googletest
  DOWNLOAD_EXTRACT_TIMESTAMP ON
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
FetchContent_MakeAvailable(googletest)

add_subdirectory(unittest)
add_subdirectory(expander)
add_subdirectory(random_test)
