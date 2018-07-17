#include "Accelerator.hpp"

namespace visualizer
{
	void Accelerator::tick()
	{
		velocity += acceleration;
		acceleration = glm::vec3();
	}
}
