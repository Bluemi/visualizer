#ifndef __QUERY_CLASS__
#define __QUERY_CLASS__

#include <vector>

#include "../../shape/ShapeSpecification.hpp"

namespace visualizer
{
	class Movable;
	enum class ShapeType;

	class Query
	{
		public:
			Query();

			Query& with_shape(const ShapeType& spec);

			bool entity_included(const Movable& movable) const;
		private:
			std::vector<ShapeType> _shape_types;
	};
}

#endif
