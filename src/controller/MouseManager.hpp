#ifndef __MOUSEMANAGER_CLASS__
#define __MOUSEMANAGER_CLASS__

#include <vector>

#include <GLFW/glfw3.h>

namespace visualizer
{
	class Controller;

	namespace MouseManager
	{
		void mouse_callback(GLFWwindow* window, double x, double y);
		void init(GLFWwindow* window);
		void add_controller(Controller* controller);
		void remove_controller(Controller* controller);
		void clear();
	}
}

#endif
