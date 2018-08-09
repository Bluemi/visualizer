#include "GroupMovementBase.hpp"

#include <iostream>

namespace visualizer
{
	GroupMovementBase::GroupMovementBase(const GroupMovement& movement)
		: _group_movement(movement)
	{}

	void GroupMovementBase::with_groups(const std::vector<std::string>& groups)
	{
		_groups.insert(_groups.end(), groups.cbegin(), groups.cend());
	}

	void GroupMovementBase::apply_to(EntityBuffer* entity_buffer)
	{
		std::visit([this, &entity_buffer](auto& m) { this->apply_to(entity_buffer, m); }, _group_movement);
	}

	template<typename GroupMovementType>
	void GroupMovementBase::apply_to(EntityBuffer* entity_buffer, GroupMovementType& movement)
	{
		if (_groups.empty())
		{
			for (auto iter = entity_buffer->begin(); iter != entity_buffer->end(); ++iter)
			{
				std::vector<Movable>& movables = iter->second;
				movement.apply_force(movables);
			}
		} else {
			for (const std::string& group : _groups)
			{
				std::vector<Movable>& movables = entity_buffer->at(group);
				movement.apply_force(movables);
			}
		}
	}
}
