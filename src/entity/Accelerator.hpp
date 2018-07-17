#ifndef __ACCELERATOR_CLASS__
#define __ACCELERATOR_CLASS__

#include <glm/glm.hpp>

namespace visualizer
{
	class Accelerator
	{
		public:
			void tick();

			glm::vec3 velocity;
			glm::vec3 acceleration;
	};
}

#endif
