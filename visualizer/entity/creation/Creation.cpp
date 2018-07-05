#include "Creation.hpp"

#include <vector>
#include "../Movable.hpp"
#include "../../shape/ShapeInitializer.hpp"

namespace visualizer
{
	Creation::Creation()
		: _quantity(0), _position(), _size(glm::vec3(1.f, 1.f, 1.f))
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

	EntityGroup Creation::create() const
	{
		unsigned int quantity = _quantity.get();

		std::vector<Movable> movables;
		movables.reserve(quantity);

		Shape shape = initialize::sphere(2, true);

		for (unsigned int i = 0; i < quantity; i++)
		{
			//Shape shape = initialize::cube(); // TODO do not create a new shape for every cube
											  // TODO clear the shape afterwards

			Movable m(shape);
			m.set_position(_position.get());
			m.set_size(_size.get());
			m.set_velocity(_velocity.get());

			movables.push_back(m);
		}

		return EntityGroup(movables);
	}
}
