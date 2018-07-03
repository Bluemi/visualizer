#include "Creation.hpp"

#include <vector>
#include "../Movable.hpp"
#include "../../ShapeInitializer.hpp"

namespace visualizer
{
	Creation::Creation()
		: _quantity(0), _position()
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

	EntityGroup Creation::create() const
	{
		unsigned int quantity = _quantity.get();

		std::vector<Movable> movables;
		movables.reserve(quantity);

		for (unsigned int i = 0; i < quantity; i++)
		{
			Shape shape = initialize::cube(); // TODO do not create a new shape for every cube
											  // TODO clear the shape afterwards

			Movable m(shape);
			m.set_position(_position.get());

			movables.push_back(m);
		}

		return EntityGroup(movables);
	}
}
