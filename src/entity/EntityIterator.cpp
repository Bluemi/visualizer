#include "EntityIterator.hpp"

namespace visualizer {
	EntityIterator::EntityIterator(const EntityBuffer::iterator& map_iterator, const std::vector<Movable>::iterator& vektor_iterator)
		: _map_iterator(map_iterator), _vektor_iterator(vektor_iterator)
	{}

	void EntityIterator::operator++() {
		_vektor_iterator++;
		if (_vektor_iterator == _map_iterator->second.end()) {
			_map_iterator++;
			_vektor_iterator = _map_iterator->second.begin();
		}
	}

	void EntityIterator::operator++(int) {
		++(*this);
	}

	bool EntityIterator::operator==(const EntityIterator& other) const {
		return _map_iterator == other._map_iterator;
	}

	bool EntityIterator::operator!=(const EntityIterator& other) const {
		return !((*this) == other);
	}

	Movable* EntityIterator::operator->() {
		return &(*_vektor_iterator);
	}

	Movable& EntityIterator::operator*() {
		return *_vektor_iterator;
	}

}
