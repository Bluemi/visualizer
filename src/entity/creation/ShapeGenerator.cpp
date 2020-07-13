#include "ShapeGenerator.hpp"

#include <iostream>

#include "../../shape/ShapeHeap.hpp"

namespace visualizer {
	const float DEFAULT_SHARE = 1.f;

	ShapeGenerator::ShapeGenerator(const ShapeSpecification& shape)
		: _shapes{_ShapeShare(shape, DEFAULT_SHARE)}
	{
		generate_sum();
	}

	ShapeGenerator::ShapeGenerator(const ShapeSpecification& shape, float share)
		: _shapes{_ShapeShare(shape, share)}
	{
		generate_sum();
	}

	ShapeGenerator& ShapeGenerator::with_shape(const ShapeSpecification& shape) {
		_shapes.push_back(_ShapeShare(shape, DEFAULT_SHARE));
		generate_sum();
		return *this;
	}

	ShapeGenerator& ShapeGenerator::with_shape(const ShapeSpecification& shape, float share) {
		_shapes.push_back(_ShapeShare(shape, share));
		generate_sum();
		return *this;
	}

	Shape ShapeGenerator::get() const {
		if (_shapes.size() == 1) {
			return g_shape_heap.get_shape(_shapes[0].specification);
		}

		float number = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/_sum));

		float counter = 0.f;
		for (const _ShapeShare& ss : _shapes) {
			counter += ss.share;
			if (counter >= number) {
				return g_shape_heap.get_shape(ss.specification);
			}
		}
		return g_shape_heap.get_shape(_shapes[_shapes.size()-1].specification);
	}

	void ShapeGenerator::generate_sum() {
		_sum = 0.f;
		for (const _ShapeShare& ss : _shapes) {
			_sum += ss.share;
		}
	}
}
