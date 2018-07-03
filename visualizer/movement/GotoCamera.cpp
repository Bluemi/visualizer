#include "GotoCamera.hpp"

#include <glm/glm.hpp>

#include "../entity/Movable.hpp"
#include "../camera/Camera.hpp"

namespace visualizer
{
	GotoCamera::GotoCamera(Camera* camera)
		: _camera(camera)
	{}

	void GotoCamera::apply_force(Movable* movable)
	{
		glm::vec3 direction = _camera->get_position() - movable->get_position();
		direction *= 0.002f;
		movable->update_acceleration(direction);
	}
}
