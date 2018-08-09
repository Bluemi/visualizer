#ifndef __GROUPMOVEMENT_CLASS__
#define __GROUPMOVEMENT_CLASS__

#include <vector>
#include <string>

#include "../EntityBuffer.hpp"
#include "Circle.hpp"

namespace visualizer
{
	using _GroupMovementVar = std::variant<Circle>;

	class GroupMovement
	{
		public:
			GroupMovement(const _GroupMovementVar& movement);
			void with_groups(const std::vector<std::string>& groups);

			void apply_to(EntityBuffer* entity_buffer);

			template<typename GroupMovementType>
			void apply_to(EntityBuffer* entity_buffer, GroupMovementType& movement);
		protected:
			std::vector<std::string> _groups;
			_GroupMovementVar _group_movement;
	};
}

#endif
