#ifndef __SHAPEHEAP_CLASS__
#define __SHAPEHEAP_CLASS__

#include <map>

#include "shape.hpp"
#include "shape_specification.hpp"

namespace visualizer {
	class ShapeHeap {
		public:
			ShapeHeap();
			~ShapeHeap();

			Shape get_shape(const ShapeSpecification& spec);
			void load_shape(const ShapeSpecification& spec);
			void close();
		private:
			std::map<ShapeSpecification, Shape*> _shapes;
	};
}

#endif
