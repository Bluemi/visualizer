#include "events.hpp"

#include <deque>

#include <GLFW/glfw3.h>

#include "../visualizer.hpp"

namespace visualizer {
	namespace events {
		void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		void mouse_callback(GLFWwindow*, double x, double y);

		// resize members
		std::vector<ResizeCallbackFunction> _resize_callbacks;

		// mouse members
		bool _first_callback = true;
		double x_last=0.0, y_last=0.0;
		std::vector<MouseCallbackFunction> _mouse_callbacks;

		void init(GLFWwindow* window) {
			glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
			glfwSetCursorPosCallback(window, mouse_callback);
		}

		// resize handling
		void register_resize_callback(const ResizeCallbackFunction& resize_callback_function) {
			_resize_callbacks.push_back(resize_callback_function);
		}

		void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
			for (ResizeCallbackFunction& rcf : _resize_callbacks) {
				rcf(width, height);
			}
		}

		// mouse handling
		void register_mouse_callback(const MouseCallbackFunction& mouse_callback_function) {
			_mouse_callbacks.push_back(mouse_callback_function);
		}

		void mouse_callback(GLFWwindow*, double x, double y) {
			if (_first_callback) {
				_first_callback = false;
			} else {
				double x_diff = x - x_last;
				double y_diff = y - y_last;

				for (MouseCallbackFunction& mcf : _mouse_callbacks) {
					mcf(x_diff, y_diff);
				}
			}
			x_last = x;
			y_last = y;
		}
	}
}
