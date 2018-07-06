#ifndef __QUERYSPACE_CLASS__
#define __QUERYSPACE_CLASS__

#include <glm/glm.hpp>

namespace visualizer
{
	class Movable;

	/**
	 * Defines a Cube Space around _center with side length = 2*size
	 * If _size == glm::vec3(0, 0, 0): All entities are considered as inside this Space.
	 */
	class QuerySpace
	{
		public:
			QuerySpace();
			QuerySpace(const glm::vec3& center, const glm::vec3& size);

			bool is_position_included(const glm::vec3& position) const;
		private:
			glm::vec3 _center;
			glm::vec3 _size;
	};
}

#endif
