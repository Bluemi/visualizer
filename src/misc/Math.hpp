#ifndef __MATH_CLASS__
#define __MATH_CLASS__

#include <glm/glm.hpp>

namespace visualizer
{
	namespace math
	{
		bool is_included(const glm::vec3& position, const glm::vec3& center, const glm::vec3& size);

		template<typename Num>
		Num limit(Num input, Num bot, Num top)
		{
			return std::max(bot, std::min(input, top));
		}
	}
}

#endif
