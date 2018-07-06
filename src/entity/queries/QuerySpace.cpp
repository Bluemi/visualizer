#include "QuerySpace.hpp"

#include "../../misc/Math.hpp"
#include "../Movable.hpp"

namespace visualizer
{
	QuerySpace::QuerySpace()
	{}

	QuerySpace::QuerySpace(const glm::vec3& center, const glm::vec3& size)
		: _center(center), _size(size)
	{}

	bool QuerySpace::is_position_included(const glm::vec3& position) const
	{
		static const glm::vec3 null_vec;
		if (_size == null_vec)
			return true;
		return math::is_included(position, _center, _size);
	}
}
