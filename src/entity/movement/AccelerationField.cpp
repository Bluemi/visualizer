#include "AccelerationField.hpp"

#include "../Movable.hpp"

namespace visualizer
{
	AccelerationField::AccelerationField()
		: _perlin_noise(3), _time(0)
	{}

	void AccelerationField::apply_force(std::vector<Movable>& movables)
	{
		for (Movable& m : movables)
		{
			apply_force(&m);
		}
		_time += 0.02f;
	}

	const float NOISE_OFFSET = 200.f;
	const float NOISE_SCALE = 0.4f;

	void AccelerationField::apply_force(Movable* movable)
	{
		float f1 = _perlin_noise({movable->get_position().x*NOISE_SCALE + NOISE_OFFSET   + _time,
								  movable->get_position().y*NOISE_SCALE + NOISE_OFFSET*2 + _time,
								  movable->get_position().z*NOISE_SCALE + NOISE_OFFSET*3 + _time});

		float f2 = _perlin_noise({movable->get_position().x*NOISE_SCALE + NOISE_OFFSET   + _time,
								  movable->get_position().y*NOISE_SCALE + NOISE_OFFSET*2 + _time,
								  movable->get_position().z*NOISE_SCALE + NOISE_OFFSET*3 + _time});
		// float f3 = _perlin_noise({movable->get_position().x + NOISE_OFFSET*2.f, movable->get_position().y + NOISE_OFFSET*2.f, movable->get_position().z + NOISE_OFFSET*2.f});
		glm::vec3 force(f1, /*movable->get_position().y */ 0.0f, f2);
		movable->update_acceleration(force*0.005f);
	}
}
