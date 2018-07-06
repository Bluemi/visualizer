#ifndef __ENTITYITERATOR_CLASS__
#define __ENTITYITERATOR_CLASS__

#include "queries/Query.hpp"

namespace visualizer
{
	class EntityBuffer;

	/**
	 * Defines an iterator over the Entities of an instance of a BufferType.
	 * The BufferType has to define a begin() and end() function.
	 */
	template<typename BufferType>
	class EntityIterator
	{
		public:
			EntityIterator(const typename BufferType::iterator& begin, const typename BufferType::iterator& end);
			EntityIterator(const typename BufferType::iterator& begin, const typename BufferType::iterator& end, const Query& query);

			void operator++();
			void operator++(int);
			Movable& operator*();
			bool operator==(const EntityIterator& other) const;
			bool operator!=(const EntityIterator& other) const;
		private:
			typename BufferType::iterator _internal_iterator;
			typename BufferType::iterator _end;
			Query _query;
	};
}

#endif
