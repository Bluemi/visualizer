#include "FlowField.hpp"

#include "../Movable.hpp"

namespace visualizer
{
	FlowField::FlowField()
		: _perlin_noise(2), _time(0)
	{}

	void FlowField::apply_force(std::vector<Movable>& movables)
	{
		for (Movable& m : movables)
		{
			apply_force(&m);
		}
	}

	const float NOISE_OFFSET = 200.f;
	const float NOISE_SCALE = 0.2f;

	void FlowField::apply_force(Movable* movable)
	{
		float f1 = _perlin_noise({movable->get_position().x*NOISE_SCALE + NOISE_OFFSET, movable->get_position().y*NOISE_SCALE + NOISE_OFFSET});
		float f2 = _perlin_noise({movable->get_position().x*NOISE_SCALE + NOISE_OFFSET*2, movable->get_position().y*NOISE_SCALE + NOISE_OFFSET*2});
		// float f3 = _perlin_noise({movable->get_position().x + NOISE_OFFSET*2.f, movable->get_position().y + NOISE_OFFSET*2.f, movable->get_position().z + NOISE_OFFSET*2.f});
		glm::vec3 force(f1, f2, 0.f);
		movable->update_acceleration(force*0.01f);
		_time += 0.01f;
	}
}
