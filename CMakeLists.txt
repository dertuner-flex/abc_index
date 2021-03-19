cmake_minimum_required(VERSION 3.5)
project(main VERSION 1.0 LANGUAGES CXX)

# add_library(abc_index INTERFACE)
include_directories(include/graph)
include_directories(include/abc_index)

file(GLOB SOURCES "src/*.cpp" "src/graph/*.cpp"
	          "src/abc_index/*.cpp")

add_executable(run ${SOURCES})
