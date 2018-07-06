#include "EntityBuffer.hpp"

namespace visualizer
{
	EntityBuffer::EntityBuffer()
	{}

	EntityBuffer::EntityBuffer(const std::vector<Movable>& movables)
		: _movables(movables)
	{}

	EntityBuffer::iterator EntityBuffer::begin()
	{
		return EntityBuffer::iterator(_movables.begin(), _movables.end());
	}

	EntityBuffer::iterator EntityBuffer::end()
	{
		return EntityBuffer::iterator(_movables.end(), _movables.end());
	}

	EntityBuffer::iterator EntityBuffer::query_iterator(const Query& query)
	{
		return EntityBuffer::iterator(_movables.begin(), _movables.end(), query);
	}

	EntityGroup EntityBuffer::query_group(const Query& query)
	{
		EntityGroup g;
		for (Movable& m : _movables)
		{
			if (query.entity_included(m))
				g.push_back(&m);
		}

		return g;
	}

	std::vector<Movable>& EntityBuffer::get_movables()
	{
		return _movables;
	}

	const std::vector<Movable>& EntityBuffer::get_movables() const
	{
		return _movables;
	}
}
