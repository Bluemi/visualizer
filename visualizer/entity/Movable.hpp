#ifndef __MOVABLE_CLASS__
#define __MOVABLE_CLASS__

#include <vector>

#include "Entity.hpp"
#include "../movement/Movement.hpp"

namespace visualizer
{
	class Movable
	{
		public:
			Movable(const Shape& shape);

			void tick();
			void render(ShaderProgram& shader_program) const;

			void add_movement(const Movement& movement);

			void set_velocity(const glm::vec3& velocity);
			glm::vec3 get_velocity() const;

			glm::vec3 get_position() const;
		private:
			Entity _entity;
			std::vector<Movement> _movements;
			glm::vec3 _velocity;
	};
}

#endif
