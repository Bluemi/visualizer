#ifndef __ENTITYGROUP_CLASS__
#define __ENTITYGROUP_CLASS__

#include "Movable.hpp"

namespace visualizer
{
	class EntityGroup
	{
		public:
			EntityGroup();
			EntityGroup(const std::vector<Movable>& movables);

			std::vector<Movable>& get_movables();
			const std::vector<Movable>& get_movables() const;
		private:
			std::vector<Movable> _movables;
	};
}

#endif
