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

	EntityBuffer::iterator EntityBuffer::query_entities(const Query& query)
	{
		return EntityBuffer::iterator(_movables.begin(), _movables.end(), query);
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
