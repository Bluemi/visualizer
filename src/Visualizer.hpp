#ifndef __VISUALIZER_CLASS__
#define __VISUALIZER_CLASS__

#include "controller/Controller.hpp"
#include "camera/Camera.hpp"
#include "entity/EntityBuffer.hpp"

namespace visualizer
{
	class Creation;
	class Query;

	class Visualizer
	{
		public:
			Visualizer();

			void init();
			void clear_window();
			void run();

			void create_entities(const Creation& creation);
			EntityBuffer& get_entities();

			void framebuffer_size_callback(GLFWwindow*, int width, int height);
		private:
			Controller _controller;
			Camera _camera;

			EntityBuffer _entities;

			GLFWwindow* _window;

			unsigned int _window_width;
			unsigned int _window_height;
	};
}

#endif
