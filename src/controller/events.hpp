#ifndef __RESIZEMANAGER_CLASS__
#define __RESIZEMANAGER_CLASS__

#include <functional>

class GLFWwindow;
class Visualizer;

namespace visualizer {
	namespace events {
		using ResizeCallbackFunction = std::function<void(int, int)>;
		using MouseCallbackFunction = std::function<void(double, double)>;

		void init(GLFWwindow* window);
		void register_resize_callback(const ResizeCallbackFunction& resize_callback_function);
		void register_mouse_callback(const MouseCallbackFunction& mouse_callback_function);
		bool has_resizing();
		std::pair<int, int> pop_resizings();
	}
}

#endif
