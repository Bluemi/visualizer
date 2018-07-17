#include "IMovement.hpp"

namespace visualizer
{
	IMovement::~IMovement() {}

	bool IMovement::should_be_removed() const
	{
		return false;
	}
}
