#include "GroupMovement.hpp"

#include <iostream>

namespace visualizer
{
	GroupMovement::GroupMovement(const _GroupMovementVar& movement)
		: _group_movement(movement)
	{}

	void GroupMovement::with_groups(const std::vector<std::string>& groups)
	{
		_groups.insert(_groups.end(), groups.cbegin(), groups.cend());
	}

	void GroupMovement::apply_to(EntityBuffer* entity_buffer)
	{
		std::visit([this, &entity_buffer](auto& m) { this->apply_to(entity_buffer, m); }, _group_movement);
	}

	template<typename GroupMovementType>
	void GroupMovement::apply_to(EntityBuffer* entity_buffer, GroupMovementType& movement)
	{
		if (_groups.empty())
		{
			for (auto iter = entity_buffer->begin(); iter != entity_buffer->end(); ++iter)
			{
				std::vector<Movable>& movables = iter->second;
				std::cout << "start apply force" << std::endl;
				movement.apply_force(movables);
				std::cout << "stop apply force" << std::endl;
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
