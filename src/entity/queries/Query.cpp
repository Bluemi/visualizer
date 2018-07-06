#include "Query.hpp"

#include "../Movable.hpp"

#include "../../shape/ShapeType.hpp"

namespace visualizer
{
	Query::Query()
	{}

	Query& Query::with_shape(const ShapeType& spec)
	{
		_shape_types.push_back(spec);
		return *this;
	}

	Query& Query::with_position(const QuerySpace& space)
	{
		_space = space;
		return *this;
	}

	bool Query::entity_included(const Movable& movable) const
	{
		bool included = true;

		bool shape_included = _shape_types.size() == 0;
		for (const ShapeType& shape_type : _shape_types)
		{
			if (shape_type == movable.get_shape_specification())
			{
				shape_included = true;
			}
		}
		included &= shape_included;

		bool position_included = _space.is_position_included(movable.get_position());
		included &= position_included;

		return included;
	}
}
