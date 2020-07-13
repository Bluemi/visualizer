#include "ResizeManager.hpp"

#include <vector>

#include <GLFW/glfw3.h>

#include "../Visualizer.hpp"

namespace visualizer {
	namespace ResizeManager {
		std::vector<Visualizer*> _visualizers;

		void init(GLFWwindow* window) {
			glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		}

		void add_visualizer(Visualizer* visualizer) {
			_visualizers.push_back(visualizer);
		}

		void remove_visualizer(Visualizer* visualizer) {
			for (auto it = _visualizers.cbegin(); it != _visualizers.cend();) {
				if (*it == visualizer) {
					it = _visualizers.erase(it);
				} else {
					++it;
				}
			}
		}

		void clear_visualizers() {
			_visualizers.clear();
		}

		void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
			for (Visualizer* visualizer : _visualizers) {
				visualizer->framebuffer_size_callback(window, width, height);
			}
		}
	}
}
