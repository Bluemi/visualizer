#ifndef __QUERY_CLASS__
#define __QUERY_CLASS__

#include <vector>

#include "../../shape/ShapeSpecification.hpp"

namespace visualizer
{
	class Movable;

	class Query
	{
		public:
			Query();

			Query& with_shape(const ShapeSpecification& spec);

			bool entity_included(const Movable& movable) const;
		private:
			std::vector<ShapeSpecification> _shapes;
	};
}

#endif
