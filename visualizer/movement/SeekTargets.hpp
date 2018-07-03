#ifndef __SEEKTARGETS_CLASS__
#define __SEEKTARGETS_CLASS__

#include <vector>

#include "IMovement.hpp"

namespace visualizer
{
	class SeekTargets : public IMovementDerivationHelper<SeekTargets>
	{
		public:
			SeekTargets(const std::vector<Movable>& targets);

			virtual void apply_force(Movable* movable) override;
		private:
			std::vector<Movable> _targets;
			unsigned int target_index;
	};
}

#endif
