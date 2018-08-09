#ifndef __ENTITYBUFFER_CLASS__
#define __ENTITYBUFFER_CLASS__

#include <unordered_map>

#include "Movable.hpp"

namespace visualizer
{
	using EntityBuffer = std::unordered_map<std::string, std::vector<Movable>>;
}

#endif
