#include "EntityIterator.hpp"

#include "Movable.hpp"

namespace visualizer
{
	template<typename BufferType>
	EntityIterator<BufferType>::EntityIterator(const typename BufferType::iterator& begin, const typename BufferType::iterator& end)
		: _internal_iterator(begin), _end(end)
	{}

	template<typename BufferType>
	EntityIterator<BufferType>::EntityIterator(const typename BufferType::iterator& begin, const typename BufferType::iterator& end, const Query& query)
		: _internal_iterator(begin), _end(end), _query(query)
	{}

	template<typename BufferType>
	void EntityIterator<BufferType>::operator++()
	{
		while (_internal_iterator != _end)
		{
			++_internal_iterator;

			if (_query.entity_included(*_internal_iterator))
			{
				break;
			}
		}
	}

	template<typename BufferType>
	void EntityIterator<BufferType>::operator++(int)
	{
		while (_internal_iterator != _end)
		{
			++_internal_iterator;

			if (_query.entity_included(*_internal_iterator))
			{
				break;
			}
		}
	}

	template<typename BufferType>
	Movable& EntityIterator<BufferType>::operator*()
	{
		return *_internal_iterator;
	}

	template<typename BufferType>
	bool EntityIterator<BufferType>::operator==(const EntityIterator& other) const
	{
		return (_internal_iterator == other._internal_iterator);
	}

	template<typename BufferType>
	bool EntityIterator<BufferType>::operator!=(const EntityIterator& other) const
	{
		return !(*this == other);
	}

	template class EntityIterator<std::vector<Movable>>;
}
