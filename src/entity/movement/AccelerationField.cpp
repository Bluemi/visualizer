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
		_time += 0.03f;
	}

	const float NOISE_OFFSET = 2000.7f;
	const float NOISE_SCALE = 0.2f;
	const float MAX_DISTANCE = 50.f;
	const float FORCE_STRENGTH = 0.003f;

	void AccelerationField::apply_force(Movable* movable)
	{
		float fx = _perlin_noise({
								  movable->get_position().x*NOISE_SCALE + NOISE_OFFSET +
								  // movable->get_position().y*NOISE_SCALE + NOISE_OFFSET,
								  movable->get_position().z*NOISE_SCALE + NOISE_OFFSET +
								  _time
								  });

		float fy = _perlin_noise({
								  movable->get_position().x*NOISE_SCALE + NOISE_OFFSET*2 +
								  // movable->get_position().y*NOISE_SCALE + NOISE_OFFSET*2 +
								  movable->get_position().z*NOISE_SCALE + NOISE_OFFSET*2 +
								  _time
								  });

		float fz = _perlin_noise({
								  movable->get_position().x*NOISE_SCALE + NOISE_OFFSET*3 +
								  // movable->get_position().y*NOISE_SCALE + NOISE_OFFSET*3,
								  movable->get_position().z*NOISE_SCALE + NOISE_OFFSET*3 +
								  _time
								  });

		movable->update_acceleration(glm::vec3(fx, fy, fz)*FORCE_STRENGTH);

		glm::vec3 mid_force = movable->get_position() * -0.00005f;
		if (std::abs(movable->get_position().x) < MAX_DISTANCE)
		{
			mid_force.x = 0.f;
		}
		mid_force.y *= 10.f;
		if (std::abs(movable->get_position().z) < MAX_DISTANCE)
		{
			mid_force.z = 0.f;
		}
		movable->update_acceleration(mid_force);
	}
}
