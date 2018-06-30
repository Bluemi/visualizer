#ifndef __VISUALIZER_CLASS__
#define __VISUALIZER_CLASS__

#include "controller/Controller.hpp"


namespace visualizer
{
	class Visualizer
	{
		public:
			Visualizer();

			void init();
			void run();

			void framebuffer_size_callback(GLFWwindow*, int width, int height);
		private:
			visualizer::Controller _controller;
			GLFWwindow* _window;

			unsigned int _window_width;
			unsigned int _window_height;
	};
}

#endif
