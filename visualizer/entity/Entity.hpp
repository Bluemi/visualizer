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

			void set_position(const glm::vec3& position);
			void update_position(const glm::vec3& velocity);

			void set_size(const glm::vec3& size);
			void update_size(const glm::vec3& size);
			glm::vec3 get_size() const;
		private:
			Shape _shape;
			glm::vec3 _position;
			glm::vec3 _size;
	};
}

#endif
