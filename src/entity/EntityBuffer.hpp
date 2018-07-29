#ifndef __ENTITYBUFFER_CLASS__
#define __ENTITYBUFFER_CLASS__

#include "Movable.hpp"
#include "EntityIterator.hpp"
#include "EntityGroup.hpp"

namespace visualizer
{
	class EntityBuffer
	{
		public:
			EntityBuffer();
			EntityBuffer(const std::vector<Movable>& movables);

			using iterator = EntityIterator<std::vector<Movable>>;

			iterator begin();
			iterator end();

			iterator query_iterator(const Query& query);
			EntityGroup query_group(const Query& query);

			void append(const EntityBuffer& entity_buffer);

			std::vector<Movable>& get_movables();
			const std::vector<Movable>& get_movables() const;
		private:
			std::vector<Movable> _movables;
	};
}

#endif
