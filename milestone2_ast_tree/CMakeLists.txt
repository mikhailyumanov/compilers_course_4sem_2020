cmake_minimum_required(VERSION 3.0)
project(Compilers)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Compilers_SOURCE_DIR}/bin)

add_subdirectory(src)
include_directories(include)
