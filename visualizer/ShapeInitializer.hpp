#ifndef __SHAPEINITIALIZER_CLASS__
#define __SHAPEINITIALIZER_CLASS__

#include <map>
#include <variant>

#include "Shape.hpp"

namespace visualizer
{
	namespace initializer
	{
		Shape initialize_cube();
		Shape initialize_sphere(unsigned int fineness);
	}
}

#endif
