#include "Misc.hpp"

namespace visualizer
{
	std::string vec_to_string(const glm::vec3& vec)
	{
		return "(" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + ")";
	}
}
