#ifndef __ENTITYBUFFER_CLASS__
#define __ENTITYBUFFER_CLASS__

#include <map>

#include "Movable.hpp"

namespace visualizer
{
	using EntityBuffer = std::map<std::string, std::vector<Movable>>;
}

#endif
