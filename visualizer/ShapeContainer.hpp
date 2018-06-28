#ifndef __SHAPECONTAINER_CLASS__
#define __SHAPECONTAINER_CLASS__

#include <map>
#include <optional>

#include "Shape.hpp"
#include "ShapeInitializer.hpp"

namespace visualizer
{
	class ShapeContainer
	{
		public:
			ShapeContainer();
			~ShapeContainer();

			void initialize(ShapeType shape_type);
			std::optional<Shape> get_shape(ShapeType shape_type);
			void bind(ShapeType shape_type);
			bool is_initialized(ShapeType shape_type) const;

		private:
			std::map<ShapeType, std::optional<Shape>> _shape_store;
	};
}

#endif
