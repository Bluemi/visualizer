#include "Creation.hpp"

#include <vector>

#include "../Movable.hpp"
#include "../../shape/ShapeInitializer.hpp"

namespace visualizer
{
	Creation::Creation(const ShapeGenerator& shape)
		: _quantity(0), _position(), _size(glm::vec3(1.f, 1.f, 1.f)), _shape(shape)
	{}

	Creation& Creation::with_quantity(const NumberGenerator<unsigned int>& quantity)
	{
		_quantity = quantity;
		return *this;
	}

	Creation& Creation::with_position(const VectorGenerator& position)
	{
		_position = position;
		return *this;
	}

	Creation& Creation::with_size(const VectorGenerator& size)
	{
		_size = size;
		return *this;
	}

	Creation& Creation::with_velocity(const VectorGenerator& velocity)
	{
		_velocity = velocity;
		return *this;
	}

	Creation& Creation::with_color(const VectorGenerator& color)
	{
		_color = color;
		return *this;
	}

	EntityBuffer Creation::create() const
	{
		unsigned int quantity = _quantity.get();

		std::vector<Movable> movables;
		movables.reserve(quantity);

		for (unsigned int i = 0; i < quantity; i++)
		{
			Movable m(_shape.get());
			m.set_position(_position.get());
			m.set_size(_size.get());
			m.set_velocity(_velocity.get());
			m.set_color(_color.get());

			movables.push_back(m);
		}

		return EntityBuffer(movables);
	}
}
