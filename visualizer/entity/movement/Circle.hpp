#ifndef __CIRCLE_CLASS__
#define __CIRCLE_CLASS__

#include <glm/glm.hpp>

#include "IMovement.hpp"

namespace visualizer
{
	class Circle : public IMovementCloneable<Circle>
	{
		public:
			Circle(const glm::vec3& center, float radius);

			virtual void apply_force(Movable* movable) override;
		private:
			glm::vec3 _center;
			float _radius;
	};
}

#endif
