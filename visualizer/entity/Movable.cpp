#include "Movable.hpp"

namespace visualizer
{
	Movable::Movable(const Shape& shape)
		: _entity(shape)
	{}

	void Movable::tick()
	{
		for (Movement& movement : _movements)
		{
			movement.apply_force(this);
		}

		_entity.update_position(_velocity);
	}

	void Movable::render(ShaderProgram& shader_program) const
	{
		_entity.render(shader_program);
	}

	void Movable::add_movement(const Movement& movement)
	{
		_movements.push_back(movement);
	}

	void Movable::set_velocity(const glm::vec3& velocity)
	{
		_velocity = velocity;
	}

	glm::vec3 Movable::get_velocity() const
	{
		return _velocity;
	}

	glm::vec3 Movable::get_position() const
	{
		return _entity.get_position();
	}
}
