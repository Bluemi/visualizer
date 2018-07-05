#ifndef __SHAPEHEAP_CLASS__
#define __SHAPEHEAP_CLASS__

#include <map>

#include "Shape.hpp"
#include "ShapeSpecification.hpp"

namespace visualizer
{
	class ShapeHeap
	{
		public:
			ShapeHeap();
			~ShapeHeap();

			Shape get_shape(const ShapeSpecification& spec);
			void load_shape(const ShapeSpecification& spec);
		private:
			std::map<ShapeSpecification, Shape*> _shapes;
	};

	extern ShapeHeap g_shape_heap;
}

#endif
