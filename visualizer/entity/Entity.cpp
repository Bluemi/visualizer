#include "Entity.hpp"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace visualizer
{
	Entity::Entity(const Shape& shape)
		: _shape(shape), _size(1.f, 1.f, 1.f)
	{}

	void Entity::render(ShaderProgram& shader_program) const
	{
		shader_program.use();
		_shape.bind();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, _position);
		// rotate
		model = glm::scale(model, _size);
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

	void Entity::set_size(const glm::vec3& size)
	{
		_size = size;
	}

	void Entity::update_size(const glm::vec3& size)
	{
		_size += size;
	}

	glm::vec3 Entity::get_size() const
	{
		return _size;
	}
}
