#ifndef __GOTOCAMERA_CLASS__
#define __GOTOCAMERA_CLASS__

#include "IMovement.hpp"

namespace visualizer
{
	class Camera;

	class GotoCamera : public IMovementCloneable<GotoCamera>
	{
		public:
			GotoCamera(Camera* camera);

			virtual void apply_force(Movable* movable) override;
		private:
			Camera* _camera;
	};
}

#endif
