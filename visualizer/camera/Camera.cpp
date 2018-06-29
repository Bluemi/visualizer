#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <math.h>

Camera::Camera()
{}

Camera::Camera(const glm::vec3 &position, const float pitch, const float yaw)
	: _position(position), _pitch(pitch), _yaw(yaw)
{}

void Camera::tick()
{
	_speed += _acceleration * CAMERA_SPEED;
	_speed *= CAMERA_DRAG;
	_position += _speed;
}

void Camera::stop()
{
	_acceleration = glm::vec3();
}

glm::vec3 Camera::get_up()
{
	return glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::vec3 Camera::get_right() const
{
	return glm::normalize(glm::cross(get_direction(), Camera::get_up()));
}

glm::vec3 Camera::get_direction() const
{
	return glm::normalize(glm::vec3(
				cos(glm::radians(_pitch)) * cos(glm::radians(_yaw)),
				sin(glm::radians(_pitch)),
				cos(glm::radians(_pitch)) * sin(glm::radians(_yaw))));
}

glm::vec3 Camera::get_top() const
{
	return glm::normalize(glm::cross(get_right(), get_direction()));
}

glm::mat4 Camera::get_look_at() const
{
	return glm::lookAt(_position, _position + get_direction(), get_up());
}

glm::vec3 Camera::get_position() const
{
	return _position;
}

void Camera::change_direction(glm::vec2 value)
{
	_yaw += value.x * CAMERA_ROTATE_SPEED;
	_pitch -= value.y * CAMERA_ROTATE_SPEED;
	_pitch = fmax(fmin(_pitch, 89.f), -89.0f);
}

void Camera::set_acceleration(const glm::vec3& acceleration)
{
	_acceleration = acceleration;
}
