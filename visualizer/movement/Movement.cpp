#include "Movement.hpp"

#include "IMovement.hpp"

namespace visualizer
{
	Movement::Movement(IMovement* imovement)
		: _imovement(imovement)
	{}

	Movement::Movement(const Movement& movement)
	{
		_imovement = movement._imovement->clone();
	}

	Movement::~Movement()
	{
		delete _imovement;
	}

	void Movement::apply_force(Movable* moveable)
	{
		_imovement->apply_force(moveable);
	}
}
