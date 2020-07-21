#include "ResizeManager.hpp"

#include <deque>

#include <GLFW/glfw3.h>

#include "../Visualizer.hpp"

namespace visualizer {
	namespace resizing {
		void framebuffer_size_callback(GLFWwindow* window, int width, int height);

		std::vector<ResizeCallbackFunction> _callbacks;

		void init(GLFWwindow* window) {
			glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		}

		void register_resize_callback(const ResizeCallbackFunction& resize_callback_function) {
			_callbacks.push_back(resize_callback_function);
		}

		void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
			for (ResizeCallbackFunction& rcf : _callbacks) {
				rcf(width, height, window);
			}
		}
	}
}
