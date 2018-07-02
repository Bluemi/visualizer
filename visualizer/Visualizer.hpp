#ifndef __VISUALIZER_CLASS__
#define __VISUALIZER_CLASS__

#include "controller/Controller.hpp"
#include "camera/Camera.hpp"

namespace visualizer
{
	class Visualizer
	{
		public:
			Visualizer();

			void init();
			void clear_window();
			void run();

			void framebuffer_size_callback(GLFWwindow*, int width, int height);
		private:
			visualizer::Controller _controller;
			visualizer::Camera _camera;

			GLFWwindow* _window;

			unsigned int _window_width;
			unsigned int _window_height;
	};
}

#endif
