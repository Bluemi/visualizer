#include "Movable.hpp"

#include <iostream>
#include "../misc/Misc.hpp"

namespace visualizer
{
	Movable::Movable(const Shape& shape)
		: _entity(shape)
	{}

	void Movable::tick(const double speed)
	{
		for (unsigned int i = 0; i < _movements.size();)
		{
			_movements[i].apply_force(this);
			if (_movements[i].should_be_removed())
			{
				_movements.erase(_movements.begin() + i);
			} else {
				i++;
			}
		}

		_position_accelerator.tick();
		_color_accelerator.tick();

		_entity.update_position(_position_accelerator.velocity * static_cast<float>(speed));
		_entity.update_color(_color_accelerator.velocity * static_cast<float>(speed));
	}

	void Movable::render(ShaderProgram& shader_program) const
	{
		_entity.render(shader_program);
	}

	void Movable::add_movement(const Movement& movement)
	{
		Movement m = movement;
		m.init(this);
		_movements.push_back(m);
	}

	void Movable::set_position(const glm::vec3& position)
	{
		_entity.set_position(position);
	}

	const glm::vec3& Movable::get_position() const
	{
		return _entity.get_position();
	}

	void Movable::update_velocity(const glm::vec3& velocity_update)
	{
		_position_accelerator.velocity += velocity_update;
	}

	void Movable::set_velocity(const glm::vec3& velocity)
	{
		_position_accelerator.velocity = velocity;
	}

	const glm::vec3& Movable::get_velocity() const
	{
		return _position_accelerator.velocity;
	}

	void Movable::update_acceleration(const glm::vec3& acceleration)
	{
		_position_accelerator.acceleration += acceleration;
	}

	void Movable::set_acceleration(const glm::vec3& acceleration)
	{
		_position_accelerator.acceleration = acceleration;
	}

	const glm::vec3& Movable::get_acceleration() const
	{
		return _position_accelerator.acceleration;
	}

	void Movable::set_size(const glm::vec3& size)
	{
		_entity.set_size(size);
	}

	void Movable::update_size(const glm::vec3& size)
	{
		_entity.update_size(size);
	}

	const glm::vec3& Movable::get_size() const
	{
		return _entity.get_size();
	}

	ShapeSpecification Movable::get_shape_specification() const
	{
		return _entity.get_shape_specification();
	}

	void Movable::set_color(const glm::vec3& color)
	{
		_entity.set_color(color);
	}

	void Movable::update_color(const glm::vec3& color)
	{
		_entity.update_color(color);
	}

	const glm::vec3& Movable::get_color() const
	{
		return _entity.get_color();
	}

	void Movable::set_color_velocity(const glm::vec3& color_velocity)
	{
		_color_accelerator.velocity = color_velocity;
	}

	void Movable::update_color_velocity(const glm::vec3& color_velocity)
	{
		_color_accelerator.velocity += color_velocity;
	}

	const glm::vec3& Movable::get_color_velocity() const
	{
		return _color_accelerator.velocity;
	}

	void Movable::set_color_acceleration(const glm::vec3& _color_acceleration)
	{
		_color_accelerator.acceleration = _color_acceleration;
	}

	void Movable::update_color_acceleration(const glm::vec3& color_acceleration)
	{
		_color_accelerator.acceleration += color_acceleration;
	}

	const glm::vec3& Movable::get_color_acceleration() const
	{
		return _color_accelerator.acceleration;
	}
}
