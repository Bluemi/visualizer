#include "timer.hpp"

#include <GLFW/glfw3.h>

namespace visualizer {
	Timer::Timer() : _offset(get_global_time()) {}

	double Timer::restart() {
		double global_time = get_global_time();
		double diff = global_time - _offset;
		_offset = global_time;
		return diff;
	}

	double Timer::get_time() const {
		return get_global_time() - _offset;
	}

	double Timer::get_global_time() {
		return glfwGetTime();
	}
}
