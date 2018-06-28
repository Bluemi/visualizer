file(GLOB_RECURSE visualizer_sources "./*.cpp")
add_library(visualizer ${visualizer_sources})

include_directories("/usr/include")

target_link_libraries(visualizer "GLU" "glfw3" "X11" "Xxf86vm" "Xrandr" "pthread" "Xi" "dl" "Xinerama" "Xcursor")
