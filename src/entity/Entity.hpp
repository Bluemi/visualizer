#ifndef __ENTITY_CLASS__
#define __ENTITY_CLASS__

#include <glm/glm.hpp>

#include "../shape/Shape.hpp"
#include "../shape/ShapeSpecification.hpp"
#include "../ShaderProgram.hpp"

namespace visualizer
{
	class Entity
	{
		public:
			Entity(const Shape& shape);

			void render(ShaderProgram& shader_program) const;
			Shape get_shape() const;
			const glm::vec3& get_position() const;

			void set_position(const glm::vec3& position);
			void update_position(const glm::vec3& velocity);

			void set_size(const glm::vec3& size);
			void update_size(const glm::vec3& size);
			const glm::vec3& get_size() const;

			void set_color(const glm::vec3& color);
			void update_color(const glm::vec3& color);
			const glm::vec3& get_color() const;

			ShapeSpecification get_shape_specification() const;
		private:
			Shape _shape;
			glm::vec3 _position;
			glm::vec3 _size;
			glm::vec3 _color;
	};
}

#endif
