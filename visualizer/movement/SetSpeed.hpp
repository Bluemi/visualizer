#ifndef __SETSPEED_CLASS__
#define __SETSPEED_CLASS__

#include "IMovement.hpp"

namespace visualizer
{
	class SetSpeed : public IMovementCloneable<SetSpeed>
	{
		public:
			SetSpeed(float x, float y, float z);

			virtual void apply_force(Movable* movable) override;
		private:
			float _x;
			float _y;
			float _z;
	};
}

#endif
