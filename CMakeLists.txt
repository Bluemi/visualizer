cmake_minimum_required (VERSION 2.6)

project(Visualizer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(visualizer)

add_executable(MainTest tests/main.cpp)
target_link_libraries(MainTest visualizer)
