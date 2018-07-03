#include "RandomAcceleration.hpp"

#include <cstdlib>
#include <glm/glm.hpp>

#include "../entity/Movable.hpp"

namespace visualizer
{
	RandomAcceleration::RandomAcceleration(float intensity, unsigned int interval)
		: _intensity(intensity), _counter(0), _interval(interval)
	{}

	float get_rand(float intensity)
	{
		return ((std::rand() % 101) - 50) / 50.f * intensity;
	}

	void RandomAcceleration::apply_force(Movable* movable)
	{
		if (_counter >= _interval)
		{
			glm::vec3 force = glm::vec3(get_rand(_intensity), get_rand(_intensity), get_rand(_intensity));
			movable->update_acceleration(force);
			_counter = 0;
		}
		_counter++;
	}
}
