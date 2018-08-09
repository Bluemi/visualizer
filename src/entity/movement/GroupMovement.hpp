#ifndef __GROUPMOVEMENT_CLASS__
#define __GROUPMOVEMENT_CLASS__

#include <variant>

#include "Circle.hpp"

namespace visualizer
{
	using GroupMovement = std::variant<Circle>;
}

#endif
