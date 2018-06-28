#include "ShapeContainer.hpp"

#include "ShapeInitializer.hpp"

namespace visualizer
{
	ShapeContainer::ShapeContainer()
	{}

	ShapeContainer::~ShapeContainer()
	{
		for (auto it=_shape_store.begin(); it!=_shape_store.end(); ++it)
		{
			(*it->second).free_buffers();
		}
	}

	void ShapeContainer::initialize(ShapeType shape_type)
	{
		if (!is_initialized(shape_type))
		{
			switch (shape_type)
			{
				case ShapeType::CUBE:
					_shape_store[ShapeType::CUBE] = initializer::initialize_cube();
					break;
				case ShapeType::SPHERE:
					_shape_store[ShapeType::SPHERE] = initializer::initialize_sphere(5);
					break;
			}
		}
	}

	std::optional<Shape> ShapeContainer::get_shape(ShapeType shape_type)
	{
		return _shape_store[shape_type];
	}

	void ShapeContainer::bind(ShapeType shape_type)
	{
		std::optional<Shape> opt_shape = _shape_store[shape_type];
		if (opt_shape)
		{
			(*opt_shape).bind();
		}
	}

	bool ShapeContainer::is_initialized(ShapeType shape_type) const
	{
		return _shape_store.find(shape_type) != _shape_store.end();
	}
}
