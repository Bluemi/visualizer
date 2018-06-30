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
		private:
			visualizer::Controller _controller;
			GLFWwindow* _window;
	};
}

#endif
