#ifndef __CREATION_CLASS__
#define __CREATION_CLASS__

#include "../EntityBuffer.hpp"
#include "NumberGenerator.hpp"
#include "VectorGenerator.hpp"
#include "ShapeGenerator.hpp"

namespace visualizer
{
	class Creation
	{
		public:
			Creation(const ShapeGenerator& shape);

			template<typename Specification>
			Creation(const Specification& spec)
				: _quantity(0), _position(), _size(glm::vec3(1.f, 1.f, 1.f)), _shape(spec)
			{}

			Creation& with_quantity(const NumberGenerator<unsigned int>& quantity);
			Creation& with_position(const VectorGenerator& position);
			Creation& with_size(const VectorGenerator& size);
			Creation& with_velocity(const VectorGenerator& velocity);
			Creation& with_color(const VectorGenerator& color);

			EntityBuffer create() const;
		private:
			NumberGenerator<unsigned int> _quantity;
			VectorGenerator _position;
			VectorGenerator _size;
			VectorGenerator _velocity;
			ShapeGenerator _shape;
			VectorGenerator _color;
	};
}

#endif
