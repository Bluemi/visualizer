#ifndef __VISUALIZER_CLASS__
#define __VISUALIZER_CLASS__

#include <optional>

#include "controller/Controller.hpp"
#include "camera/Camera.hpp"
#include "entity/EntityBuffer.hpp"
#include "entity/EntityReferences.hpp"
#include "entity/queries/Query.hpp"
#include "entity/movement/GroupMovement.hpp"
#include "ShaderProgram.hpp"

namespace visualizer
{
	class Creation;

	class Visualizer
	{
		public:
			Visualizer(GLFWwindow* window, ShaderProgram shader_program, unsigned int window_width, unsigned int window_height);
			Visualizer(const Visualizer& visu);
			~Visualizer();

			static void init();
			static std::optional<Visualizer> create(unsigned int window_width, unsigned int window_height);

			void tick();
			void render();
			void close();
			bool should_close() const;

			double get_time() const;

			void create_entities(const Creation& creation);
			EntityBuffer& get_entities();
			EntityReferences query_entities(const Query& query);

			void add_group_movement(const GroupMovement& movement);

			void framebuffer_size_callback(GLFWwindow*, int width, int height);
		private:
			double get_delta_time();
			void clear_window();

			Controller _controller;
			Camera _camera;
			ShaderProgram _shader_program;

			EntityBuffer _entities;
			std::vector<GroupMovement> _group_movements;

			GLFWwindow* _window;

			double _last_frame_time;

			unsigned int _window_width;
			unsigned int _window_height;
	};
}

#endif
