#ifndef __RESIZEMANAGER_CLASS__
#define __RESIZEMANAGER_CLASS__

class GLFWwindow;
class Visualizer;

namespace visualizer
{
	namespace ResizeManager
	{
		void init(GLFWwindow* window);
		void add_visualizer(Visualizer* visualizer);
		void remove_visualizer(Visualizer* visualizer);
		void clear_visualizers();
		void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	}
}

#endif
