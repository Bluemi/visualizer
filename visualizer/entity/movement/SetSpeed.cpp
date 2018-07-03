#include "SetSpeed.hpp"

#include "../Movable.hpp"

namespace visualizer
{
	SetSpeed::SetSpeed(float x, float y, float z)
		: _x(x), _y(y), _z(z)
	{}

	void SetSpeed::apply_force(Movable* movable)
	{
		movable->set_velocity(glm::vec3(_x, _y, _z));
	}
}
