#include "Visualizer.hpp"
#include "entity/creation/Creation.hpp"
#include "entity/creation/VectorGenerator.hpp"
#include "entity/creation/ShapeGenerator.hpp"
#include "shape/ShapeSpecification.hpp"
#include "shape/ShapeHeap.hpp"

#include <glm/glm.hpp>

int main() {
	visualizer::Visualizer visualizer;
	visualizer.init();

	visualizer::VectorGenerator pos_gen = visualizer::VectorGenerator().with_stddev(glm::vec3(5.f, 5.f, 5.f));
	visualizer::VectorGenerator size_gen = visualizer::VectorGenerator(glm::vec3(0.05f, 0.05f, 0.05f)).with_stddev(glm::vec3(0.01f));
	visualizer::VectorGenerator speed_gen = visualizer::VectorGenerator().with_stddev(glm::vec3(1.f, 1.f, 1.f));
	visualizer::ShapeGenerator shape_gen = visualizer::ShapeGenerator(visualizer::SphereSpecification(2), 1.f).with_shape(visualizer::CubeSpecification(), 0.2f);

	visualizer::Creation creation = visualizer::Creation(shape_gen)
		.with_quantity(2000)
		.with_position(pos_gen)
		.with_size(size_gen)
		.with_velocity(speed_gen);

	visualizer.create_entities(creation);

	visualizer.run();
	return 0;
}
