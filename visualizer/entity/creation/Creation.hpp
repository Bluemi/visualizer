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
			Creation& with_size(const VectorGenerator& size);
			Creation& with_velocity(const VectorGenerator& velocity);

			EntityGroup create() const;
		private:
			NumberGenerator<unsigned int> _quantity;
			VectorGenerator _position;
			VectorGenerator _size;
			VectorGenerator _velocity;
	};
}

#endif
