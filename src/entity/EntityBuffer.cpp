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

	void EntityBuffer::append(const EntityBuffer& entity_buffer)
	{
		_movables.insert(_movables.begin(), entity_buffer.get_movables().cbegin(), entity_buffer.get_movables().cend());
	}

	std::vector<Movable>& EntityBuffer::get_movables()
	{
		return const_cast<std::vector<Movable>&>(
				static_cast<const EntityBuffer&>(*this)
					.get_movables());
	}

	const std::vector<Movable>& EntityBuffer::get_movables() const
	{
		return _movables;
	}
}
