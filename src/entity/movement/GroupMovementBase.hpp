#ifndef __GROUPMOVEMENTBASE_CLASS__
#define __GROUPMOVEMENTBASE_CLASS__

#include <vector>
#include <string>

#include "../EntityBuffer.hpp"
#include "GroupMovement.hpp"

namespace visualizer
{
	class GroupMovementBase
	{
		public:
			GroupMovementBase(const GroupMovement& movement);
			void with_groups(const std::vector<std::string>& groups);

			void apply_to(EntityBuffer* entity_buffer);
			template<typename GroupMovementType>
			void apply_to(EntityBuffer* entity_buffer, GroupMovementType& movement);
		protected:
			std::vector<std::string> _groups;
			GroupMovement _group_movement;
	};
}

#endif
