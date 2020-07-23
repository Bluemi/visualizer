#include "shape_heap.hpp"

#include "shape_initialization.hpp"

namespace visualizer {
	ShapeHeap::ShapeHeap() {}

	ShapeHeap::~ShapeHeap() {
		close();
	}

	void ShapeHeap::load_shape(const ShapeSpecification& spec) {
		auto it = _shapes.find(spec);
		if (it == _shapes.end()) {
			_shapes[spec] = new Shape(initialize::create_shape(spec));
		}
	}

	Shape ShapeHeap::get_shape(const ShapeSpecification& spec) {
		auto it = _shapes.find(spec);
		Shape* shape;
		if (it == _shapes.end()) {
			shape = new Shape(initialize::create_shape(spec));
			_shapes[spec] = shape;
		} else {
			shape = it->second;
		}
		return Shape(*shape);
	}

	void ShapeHeap::close() {
		for (auto& s : _shapes) {
			s.second->free_buffers();
			delete s.second;
		}
		_shapes.clear();
	}
}
