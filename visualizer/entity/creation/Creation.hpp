#ifndef __CREATION_CLASS__
#define __CREATION_CLASS__

#include "../EntityGroup.hpp"
#include "NumberGenerator.hpp"
#include "VectorGenerator.hpp"

namespace visualizer
{
	class Creation
	{
		public:
			Creation();

			Creation& with_quantity(const NumberGenerator<unsigned int>& quantity);
			Creation& with_position(const VectorGenerator& position);

			EntityGroup create() const;
		private:
			NumberGenerator<unsigned int> _quantity;
			VectorGenerator _position;
	};
}

#endif
