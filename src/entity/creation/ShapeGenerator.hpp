#ifndef __SHAPEGENERATOR_CLASS__
#define __SHAPEGENERATOR_CLASS__

#include <vector>

#include "../../shape/Shape.hpp"
#include "../../shape/ShapeSpecification.hpp"

namespace visualizer {
	struct _ShapeShare {
		_ShapeShare(const ShapeSpecification& spec, float s) : specification(spec), share(s) {}

		ShapeSpecification specification;
		float share;
	};

	class ShapeGenerator {
		public:
			ShapeGenerator(const ShapeSpecification& shape);
			ShapeGenerator(const ShapeSpecification& shape, float share);

			ShapeGenerator& with_shape(const ShapeSpecification& shape);
			ShapeGenerator& with_shape(const ShapeSpecification& shape, float share);

			Shape get() const;
		private:
			void generate_sum();

			std::vector<_ShapeShare> _shapes;
			float _sum;
	};
}

#endif
