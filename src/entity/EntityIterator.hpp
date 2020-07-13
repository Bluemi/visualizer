#ifndef __ENTITYITERATOR_CLASS__
#define __ENTITYITERATOR_CLASS__

#include "EntityBuffer.hpp"

namespace visualizer {
	class EntityIterator {
		public:
			EntityIterator(const EntityBuffer::iterator& map_iterator, const std::vector<Movable>::iterator& vektor_iterator);
			void operator++();
			void operator++(int);

			bool operator==(const EntityIterator& other) const;
			bool operator!=(const EntityIterator& other) const;

			Movable* operator->();
			Movable& operator*();
		private:
			EntityBuffer::iterator _map_iterator;
			std::vector<Movable>::iterator _vektor_iterator;
	};
}

#endif
