#ifndef __VISUALIZER_CLASS__
#define __VISUALIZER_CLASS__

#include "controller/Controller.hpp"

class Visualizer
{
	public:
		Visualizer();

		void run();
	private:
		visualizer::Controller _controller;
};

#endif
