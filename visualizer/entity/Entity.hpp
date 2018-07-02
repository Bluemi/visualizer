#ifndef __ENTITY_CLASS__
#define __ENTITY_CLASS__

#include <glm/glm.hpp>

#include "../Shape.hpp"
#include "../ShaderProgram.hpp"

namespace visualizer
{
	class Entity
	{
		public:
			Entity(const Shape& shape);

			void render(ShaderProgram& shader_program) const;
			Shape get_shape() const;
			glm::vec3 get_position() const;

			void update_position(const glm::vec3& velocity);
		private:
			Shape _shape;
			glm::vec3 _position;
	};
}

#endif
