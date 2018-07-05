#ifndef __MISC_CLASS__
#define __MISC_CLASS__

#include <string>
#include <glm/glm.hpp>

namespace visualizer
{
	std::string vec_to_string(const glm::vec3& vec);

	float generate_float(float mean, float stddev);
	int generate_int(int mean, int stddev);
	unsigned int generate_uint(unsigned int min, unsigned int max);
}

#endif
