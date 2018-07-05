#ifndef __SHAPESPECIFICATION_CLASS__
#define __SHAPESPECIFICATION_CLASS__

#include "Shape.hpp"

namespace visualizer
{
	/**
	 * Helper class to provide relation operators (no polymorphism needed)
	 */
	template<typename Specification>
	class SpecificationOperators
	{
		public:
			bool operator<(const Specification&) const { return false; }
			bool operator<=(const Specification&) const { return false; }
			bool operator>(const Specification&) const { return false; }
			bool operator>=(const Specification&) const { return false; }
	};

	class CubeSpecification : public SpecificationOperators<CubeSpecification> {};

	class SphereSpecification : public SpecificationOperators<SphereSpecification>
	{
		public:
			SphereSpecification(unsigned int fineness);
			bool operator==(const SphereSpecification& spec) const;

			unsigned int get_fineness() const;
		private:
			unsigned int _fineness;
	};

	using ShapeSpecification = std::variant<CubeSpecification, SphereSpecification>;

	namespace initialize
	{
		Shape create_shape(const ShapeSpecification& spec);
	}
}

#endif
