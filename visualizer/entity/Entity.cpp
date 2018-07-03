#include "Entity.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace visualizer
{
	Entity::Entity(const Shape& shape)
		: _shape(shape)
	{}

	void Entity::render(ShaderProgram& shader_program) const
	{
		shader_program.use();
		_shape.bind();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, _position);
		shader_program.set_4fv("model", model);

		glDrawArrays(GL_TRIANGLES, 0, _shape.get_number_vertices());
	}

	Shape Entity::get_shape() const
	{
		return _shape;
	}

	glm::vec3 Entity::get_position() const
	{
		return _position;
	}

	void Entity::set_position(const glm::vec3& position)
	{
		_position = position;
	}

	void Entity::update_position(const glm::vec3& velocity)
	{
		_position += velocity;
	}
}
