#ifndef __ENTITYBUFFER_CLASS__
#define __ENTITYBUFFER_CLASS__

#include "Movable.hpp"
#include "EntityIterator.hpp"

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

			iterator query_entities(const Query& query);

			std::vector<Movable>& get_movables();
			const std::vector<Movable>& get_movables() const;
		private:
			std::vector<Movable> _movables;
	};
}

#endif
