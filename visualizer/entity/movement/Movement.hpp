#ifndef __MOVEMENT_CLASS__
#define __MOVEMENT_CLASS__

namespace visualizer
{
	class IMovement;
	class Movable;

	class Movement
	{
		public:
			Movement(IMovement* imovement);
			Movement(const Movement& movement);
			~Movement();

			void apply_force(Movable* moveable);
		private:
			IMovement* _imovement;
	};
}

#endif
