#include "StdColor.hpp"

#include "../Movable.hpp"

namespace visualizer {
	StdColor::StdColor(float strength)
		: _strength(strength), _color(0.f, 0.f, 0.f)
	{}

	void StdColor::init(Movable* movable) {
		_color = movable->get_color();
	}

	void StdColor::apply_force(Movable* movable) {
		glm::vec3 direction = (_color - movable->get_color()) * _strength;
		movable->update_color_acceleration(direction);
	}
}
