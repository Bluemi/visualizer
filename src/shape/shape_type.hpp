#ifndef __SHAPETYPE_CLASS__
#define __SHAPETYPE_CLASS__

#include "shape_specification.hpp"

namespace visualizer {
	enum class ShapeType {
		CUBE,
		SPHERE
	};

	bool operator==(const ShapeType& shape_type, const ShapeSpecification& shape_spec);
	bool operator==(const ShapeSpecification& shape_spec, const ShapeType& shape_type);

	ShapeType specification_to_type(const ShapeSpecification& spec);
}

#endif
