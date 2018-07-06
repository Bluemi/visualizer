#ifndef __MOVABLE_CLASS__
#define __MOVABLE_CLASS__

#include <vector>

#include "Entity.hpp"
#include "movement/Movement.hpp"
#include "../shape/ShapeSpecification.hpp"

namespace visualizer
{
	class Movable
	{
		public:
			Movable(const Shape& shape);

			void tick();
			void render(ShaderProgram& shader_program) const;

			void add_movement(const Movement& movement);

			void set_position(const glm::vec3& position);
			glm::vec3 get_position() const;

			void update_velocity(const glm::vec3& acceleration);
			void set_velocity(const glm::vec3& velocity);
			glm::vec3 get_velocity() const;

			void update_acceleration(const glm::vec3& acceleration);
			void set_acceleration(const glm::vec3& acceleration);
			glm::vec3 get_acceleration() const;

			void set_size(const glm::vec3& size);
			void update_size(const glm::vec3& size);
			glm::vec3 get_size() const;

			ShapeSpecification get_shape_specification() const;
		private:
			Entity _entity;
			std::vector<Movement> _movements;
			glm::vec3 _velocity;
			glm::vec3 _acceleration;
	};
}

#endif
