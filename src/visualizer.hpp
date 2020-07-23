#ifndef __VISUALIZER_CLASS__
#define __VISUALIZER_CLASS__

#include <optional>

#include "controller/controller.hpp"
#include "camera/camera.hpp"
#include "shader_program.hpp"

namespace visualizer {
	class Creation;

	class Visualizer {
		public:
			Visualizer(GLFWwindow* window, ShaderProgram shader_program, unsigned int window_width, unsigned int window_height);
			Visualizer(const Visualizer& visu);
			~Visualizer();

			static void init();
			static std::optional<Visualizer> create(unsigned int window_width, unsigned int window_height, const std::string& window_name);

			void tick();
			void render();
			void close();
			bool should_close() const;

			double get_time() const;

			void framebuffer_size_callback(GLFWwindow*, int width, int height);
		private:
			double get_delta_time();
			void clear_window();

			Controller _controller;
			Camera _camera;
			ShaderProgram _shader_program;

			GLFWwindow* _window;

			double _last_frame_time;

			unsigned int _window_width;
			unsigned int _window_height;
	};

	void init();
	void clear_window();
	void close();
}

#endif
