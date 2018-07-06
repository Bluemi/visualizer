#include "EntityGroup.hpp"

namespace visualizer
{
	EntityGroup::EntityGroup()
	{}

	EntityGroup::EntityGroup(const std::vector<Movable>& movables)
		: _movables(movables)
	{}

	std::vector<Movable>& EntityGroup::get_movables()
	{
		return _movables;
	}

	const std::vector<Movable>& EntityGroup::get_movables() const
	{
		return _movables;
	}
}
