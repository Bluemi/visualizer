#ifndef __ACCELERATIONFIELD_CLASS__
#define __ACCELERATIONFIELD_CLASS__

#include <vector>

#include "../../misc/PerlinNoise.hpp"

namespace visualizer
{
	class Movable;

	class AccelerationField
	{
		public:
			AccelerationField();

			void apply_force(std::vector<Movable>& movables);
			void apply_force(Movable* movable);
		private:
			PerlinNoise _perlin_noise;
			float _time;
	};
}

#endif
