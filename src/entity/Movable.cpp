#include "Movable.hpp"

namespace visualizer
{
	Movable::Movable(const Shape& shape)
		: _entity(shape)
	{}

	void Movable::tick(const double speed)
	{
		for (Movement& movement : _movements)
		{
			movement.apply_force(this);
		}

		_velocity += _acceleration;
		_acceleration = glm::vec3();

		_entity.update_position(_velocity * static_cast<float>(speed));
	}

	void Movable::render(ShaderProgram& shader_program) const
	{
		_entity.render(shader_program);
	}

	void Movable::add_movement(const Movement& movement)
	{
		_movements.push_back(movement);
	}

	void Movable::set_position(const glm::vec3& position)
	{
		_entity.set_position(position);
	}

	glm::vec3 Movable::get_position() const
	{
		return _entity.get_position();
	}

	void Movable::update_velocity(const glm::vec3& acceleration)
	{
		_velocity += acceleration;
	}

	void Movable::set_velocity(const glm::vec3& velocity)
	{
		_velocity = velocity;
	}

	glm::vec3 Movable::get_velocity() const
	{
		return _velocity;
	}

	void Movable::update_acceleration(const glm::vec3& acceleration)
	{
		_acceleration += acceleration;
	}

	void Movable::set_acceleration(const glm::vec3& acceleration)
	{
		_acceleration = acceleration;
	}

	glm::vec3 Movable::get_acceleration() const
	{
		return _acceleration;
	}

	void Movable::set_size(const glm::vec3& size)
	{
		_entity.set_size(size);
	}

	void Movable::update_size(const glm::vec3& size)
	{
		_entity.update_size(size);
	}

	glm::vec3 Movable::get_size() const
	{
		return _entity.get_size();
	}

	ShapeSpecification Movable::get_shape_specification() const
	{
		return _entity.get_shape_specification();
	}
}
