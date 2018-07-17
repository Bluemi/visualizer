#include "Entity.hpp"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "../misc/Math.hpp"

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

		shader_program.set_3f("color", _color);

		glDrawArrays(GL_TRIANGLES, 0, _shape.get_number_vertices());
	}

	Shape Entity::get_shape() const
	{
		return _shape;
	}

	const glm::vec3& Entity::get_position() const
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
	const glm::vec3& Entity::get_size() const
	{
		return _size;
	}

	ShapeSpecification Entity::get_shape_specification() const
	{
		return _shape.get_specification();
	}

	void Entity::set_color(const glm::vec3& color)
	{
		for (int i = 0; i < _color.length(); i++)
		{
			_color[i] = math::limit(color[i], 0.f, 1.f);
		}
	}

	void Entity::update_color(const glm::vec3& color)
	{
		set_color(_color + color);
	}

	const glm::vec3& Entity::get_color() const
	{
		return _color;
	}
}
