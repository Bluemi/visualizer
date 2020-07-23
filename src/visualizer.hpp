#ifndef __VISUALIZER_CLASS__
#define __VISUALIZER_CLASS__

#include <optional>

#include "controller/controller.hpp"
#include "camera/camera.hpp"
#include "shader_program.hpp"

namespace visualizer {
	void init();
	GLFWwindow* create_window(int width, int height);
	bool should_close(GLFWwindow* window);
	void clear_window();
	void close();
}

#endif
