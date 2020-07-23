#include "visualizer.hpp"

#include <cmath>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace visualizer {
	GLFWwindow* create_window(int width, int height) {
		GLFWwindow* window = glfwCreateWindow(width, height, "Visualizer", NULL, NULL);
		if (window == NULL) {
			glfwTerminate();
			return NULL;
		}

		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			return NULL;
		}

		glViewport(0, 0, width, height);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glEnable(GL_DEPTH_TEST);

		return window;
	}

	void clear_window() {
		glClearColor(0.05f, 0.07f, 0.08f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void init() {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	}

	void close() {
		glfwTerminate();
	}
}
