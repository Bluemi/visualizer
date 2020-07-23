#include "MouseManager.hpp"

#include "controller.hpp"

namespace visualizer {
	namespace MouseManager {
		std::vector<Controller*> _controllers;
		bool _first_callback = true;
		double x_last, y_last;

		void mouse_callback(GLFWwindow*, double x, double y) {
			double x_diff, y_diff;
			if (_first_callback) {
				_first_callback = false;
			} else {
				x_diff = x - x_last;
				y_diff = y - y_last;

				for (Controller* c : _controllers) {
					c->mouse_callback(x_diff, y_diff);
				}
			}
			x_last = x;
			y_last = y;
		}

		void init(GLFWwindow* window) {
			glfwSetCursorPosCallback(window, mouse_callback);
		}

		void add_controller(Controller* controller) {
			_controllers.push_back(controller);
		}

		void remove_controller(Controller* controller) {
			for (auto it = _controllers.begin(); it != _controllers.end(); ++it) {
				if (*it == controller) {
					_controllers.erase(it);
					break;
				}
			}
		}

		void clear() {
			_controllers.clear();
		}
	}
}
