#include "Query.hpp"

#include "../Movable.hpp"

namespace visualizer
{
	Query::Query()
	{}

	Query& Query::with_shape(const ShapeSpecification& spec)
	{
		_shapes.push_back(spec);
		return *this;
	}

	bool Query::entity_included(const Movable& movable) const
	{
		bool included = true;

		bool shape_included = _shapes.size() == 0;
		for (const ShapeSpecification& shape_specification : _shapes)
		{
			if (movable.get_shape_specification() == shape_specification)
			{
				shape_included = true;
			}
		}
		included &= shape_included;

		return included;
	}
}
