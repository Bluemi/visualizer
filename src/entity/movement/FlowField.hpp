#ifndef __FLOWFIELD_CLASS__
#define __FLOWFIELD_CLASS__

#include <vector>

#include "../../misc/PerlinNoise.hpp"

namespace visualizer
{
	class Movable;

	class FlowField
	{
		public:
			FlowField();

			void apply_force(std::vector<Movable>& movables);
			void apply_force(Movable* movable);
		private:
			PerlinNoise _perlin_noise;
			float _time;
	};
}

#endif
