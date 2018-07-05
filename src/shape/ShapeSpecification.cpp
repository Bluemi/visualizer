#include "ShapeSpecification.hpp"

#include "ShapeInitializer.hpp"

namespace visualizer
{
	SphereSpecification::SphereSpecification(unsigned int fineness)
		: _fineness(fineness)
	{}

	bool SphereSpecification::operator==(const SphereSpecification& spec) const
	{
		return _fineness == spec._fineness;
	}

	unsigned int SphereSpecification::get_fineness() const
	{
		return _fineness;
	}

	class ShapeExtractor
	{
		public:
			Shape operator()(const CubeSpecification&)
			{
				return initialize::cube();
			}

			Shape operator()(const SphereSpecification& spec)
			{
				return initialize::sphere(spec.get_fineness(), true);
			}
	} shape_extractor;

	namespace initialize
	{
		Shape create_shape(const ShapeSpecification& spec)
		{
			return std::visit(shape_extractor, spec);
		}
	}
}
