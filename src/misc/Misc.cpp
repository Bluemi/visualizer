#include "Misc.hpp"

#include <random>

namespace visualizer {
	std::default_random_engine _generator;

	std::string vec_to_string(const glm::vec3& vec) {
		return "(" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + ")";
	}

	float generate_float(float mean, float stddev) {
		if (stddev == 0.f) {
			return mean;
		}
		std::normal_distribution<float> distribution(mean, stddev);
		return distribution(_generator);
	}

	int generate_int(int mean, int stddev) {
		return (std::rand() % (stddev*2+1)) - stddev + mean;
	}

	unsigned int generate_uint(unsigned int min, unsigned int max) {
		if (min > max) {
			return 0;
		}
		const unsigned int width = max - min;
		const unsigned int n = std::rand() % (width+1);
		return n + min;
	}
}
