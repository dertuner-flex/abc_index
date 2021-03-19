cmake_minimum_required(VERSION 3.5)
project(main VERSION 1.0 LANGUAGES CXX)

# add_library(abc_index INTERFACE)
include_directories(include/graph)

file(GLOB SOURCES "src/*.cpp" "src/graph/*.cpp")

add_executable(run ${SOURCES})
