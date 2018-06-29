#include "Controller.hpp"

#include "../camera/Camera.hpp"

namespace visualizer
{
	const KeyType Controller::CAMERA_FORWARD_KEY = GLFW_KEY_W;
	const KeyType Controller::CAMERA_BACKWARD_KEY = GLFW_KEY_S;
	const KeyType Controller::CAMERA_LEFT_KEY = GLFW_KEY_A;
	const KeyType Controller::CAMERA_RIGHT_KEY = GLFW_KEY_D;
	const KeyType Controller::CLOSE_KEY = GLFW_KEY_ESCAPE;

	Controller::Controller() : Controller(nullptr)
	{}

	Controller::Controller(Camera* camera)
		: _camera(camera)
	{
		std::vector<KeyType> keys_to_track = {CAMERA_LEFT_KEY,
											  CAMERA_RIGHT_KEY,
											  CAMERA_FORWARD_KEY,
											  CAMERA_BACKWARD_KEY,
											  CLOSE_KEY};

		for (KeyType key : keys_to_track)
		{
			_is_pressed[key] = false;
		}
	}

	void Controller::instruct_camera(Camera* camera)
	{
		_camera = camera;
	}

	void Controller::process_user_input(GLFWwindow* window)
	{
		for (auto it = _is_pressed.begin(); it != _is_pressed.end(); ++it)
		{
			const bool key_pressed = glfwGetKey(window, it->first) == GLFW_PRESS;
			if (key_pressed != it->second)
			{
				it->second = key_pressed;
				if (key_pressed) {
					this->key_pressed(window, it->first);
				} else {
					this->key_released(window, it->first);
				}
			}
		}

		glm::vec3 acceleration;
		if (_is_pressed[CAMERA_FORWARD_KEY])
			acceleration.z -= 1.f;
		if (_is_pressed[CAMERA_BACKWARD_KEY])
			acceleration.z += 1.f;
		if (_is_pressed[CAMERA_RIGHT_KEY])
			acceleration.x += 1.f;
		if (_is_pressed[CAMERA_LEFT_KEY])
			acceleration.x -= 1.f;

		if (_camera != nullptr)
			_camera->set_acceleration(acceleration);
	}

	void Controller::key_pressed(GLFWwindow* window, KeyType key)
	{
		if (key == CLOSE_KEY)
			glfwSetWindowShouldClose(window, true);
	}

	void Controller::key_released(GLFWwindow*, KeyType)
	{
	}
}
