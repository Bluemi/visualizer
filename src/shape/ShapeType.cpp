#include "ShapeType.hpp"

#include <variant>

namespace visualizer
{
	bool operator==(const ShapeType& shape_type, const ShapeSpecification& shape_spec)
	{
		return shape_type == specification_to_type(shape_spec);
	}

	bool operator==(const ShapeSpecification& shape_spec, const ShapeType& shape_type)
	{
		return shape_type == shape_spec;
	}

	class CubeSpecification;
	class SphereSpecification;

	struct TypeExtractor
	{
		ShapeType operator()(const CubeSpecification&)
		{
			return ShapeType::CUBE;
		}

		ShapeType operator()(const SphereSpecification&)
		{
			return ShapeType::SPHERE;
		}
	} _type_extractor;

	ShapeType specification_to_type(const ShapeSpecification& spec)
	{
		return std::visit(_type_extractor, spec);
	}
}
