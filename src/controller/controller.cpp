#include "controller.hpp"

#include <iostream>

#include <GLFW/glfw3.h>

#include "../camera/camera.hpp"

namespace visualizer {
	const Key Controller::CAMERA_FORWARD_KEY = GLFW_KEY_W;
	const Key Controller::CAMERA_BACKWARD_KEY = GLFW_KEY_S;
	const Key Controller::CAMERA_LEFT_KEY = GLFW_KEY_A;
	const Key Controller::CAMERA_RIGHT_KEY = GLFW_KEY_D;
	const Key Controller::CAMERA_TOP_KEY = GLFW_KEY_SPACE;
	const Key Controller::CAMERA_BOTTOM_KEY = GLFW_KEY_LEFT_CONTROL;
	const Key Controller::CLOSE_KEY = GLFW_KEY_ESCAPE;

	Controller::Controller() {
		std::vector<Key> keys_to_track = {CAMERA_LEFT_KEY,
											  CAMERA_RIGHT_KEY,
											  CAMERA_FORWARD_KEY,
											  CAMERA_BACKWARD_KEY,
											  CLOSE_KEY};

		for (Key key : keys_to_track) {
			_is_pressed[key] = false;
		}
	}

	void Controller::mouse_callback(double x, double y) {
		x_change += x;
		y_change += y;
	}

	void Controller::process_user_input(GLFWwindow* window, Camera* camera) {
		for (auto it = _is_pressed.begin(); it != _is_pressed.end(); ++it) {
			const bool key_pressed = glfwGetKey(window, it->first) == GLFW_PRESS;
			if (key_pressed != it->second) {
				it->second = key_pressed;
				if (key_pressed) {
					this->key_pressed(window, it->first);
				} else {
					this->key_released(window, it->first);
				}
			}
		}

		process_camera(camera);
	}

	void Controller::process_camera(Camera* camera) {
		glm::vec3 acceleration(0.f, 0.f, 0.f);
		if (_is_pressed[CAMERA_FORWARD_KEY])
			acceleration.x += 1.f;
		if (_is_pressed[CAMERA_BACKWARD_KEY])
			acceleration.x -= 1.f;
		if (_is_pressed[CAMERA_RIGHT_KEY])
			acceleration.z += 1.f;
		if (_is_pressed[CAMERA_LEFT_KEY])
			acceleration.z -= 1.f;
		if (_is_pressed[CAMERA_TOP_KEY])
			acceleration.y += 1.f;
		if (_is_pressed[CAMERA_BOTTOM_KEY])
			acceleration.y -= 1.f;

		if (camera != nullptr) {
			camera->set_acceleration(acceleration);
			camera->change_direction(glm::vec2(x_change, y_change));
			x_change = 0.0;
			y_change = 0.0;
		}
	}

	void Controller::key_pressed(GLFWwindow* window, Key key) {
		if (key == CLOSE_KEY)
			glfwSetWindowShouldClose(window, true);
	}

	void Controller::key_released(GLFWwindow*, Key) {
	}
}
