add_executable(MainTest main.cpp)

include_directories(VISUALIZER_SOURCE_DIR)

target_link_libraries(MainTest "visualizer")
