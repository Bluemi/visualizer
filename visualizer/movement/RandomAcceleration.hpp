#ifndef __RANDOMACCELERATION_CLASS__
#define __RANDOMACCELERATION_CLASS__

#include "IMovement.hpp"

namespace visualizer
{
	class Movable;

	class RandomAcceleration : public IMovementCloneable<RandomAcceleration>
	{
		public:
			RandomAcceleration(float intensity, unsigned int interval);

			virtual void apply_force(Movable* movable) override;
		private:
			float _intensity;
			unsigned int _counter;
			unsigned int _interval;
	};
}

#endif
