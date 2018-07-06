#ifndef __QUERY_CLASS__
#define __QUERY_CLASS__

#include <vector>

#include "../../shape/ShapeSpecification.hpp"
#include "QuerySpace.hpp"

namespace visualizer
{
	class Movable;
	enum class ShapeType;

	class Query
	{
		public:
			Query();

			Query& with_shape(const ShapeType& spec);
			Query& with_position(const QuerySpace& space);

			bool entity_included(const Movable& movable) const;
		private:
			std::vector<ShapeType> _shape_types;
			QuerySpace _space;
	};
}

#endif
