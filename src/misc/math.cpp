#include "math.hpp"

namespace visualizer {
	namespace math {
		bool is_included(const glm::vec3& position, const glm::vec3& center, const glm::vec3& size) {
			bool included = true;
			for (auto dimension = 0; dimension < position.length(); dimension++) {
				if (position[dimension] < (center[dimension] - size[dimension])) {
					included = false;
					break;
				}
				if (position[dimension] > (center[dimension] + size[dimension])) {
					included = false;
					break;
				}
			}
			return included;
		}
	}
}
