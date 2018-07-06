#include <iostream>

#include "Visualizer.hpp"
#include "entity/creation/Creation.hpp"
#include "entity/creation/VectorGenerator.hpp"
#include "entity/creation/ShapeGenerator.hpp"
#include "entity/EntityGroup.hpp"
#include "shape/ShapeSpecification.hpp"
#include "shape/ShapeHeap.hpp"
#include "entity/queries/Query.hpp"

#include <glm/glm.hpp>

int main() {
	visualizer::Visualizer visualizer;
	visualizer.init();

	visualizer::VectorGenerator pos_gen = visualizer::VectorGenerator().with_stddev(glm::vec3(5.f, 5.f, 5.f));
	visualizer::VectorGenerator size_gen = visualizer::VectorGenerator(glm::vec3(0.05f, 0.05f, 0.05f)).with_stddev(glm::vec3(0.01f));
	visualizer::VectorGenerator speed_gen = visualizer::VectorGenerator().with_stddev(glm::vec3(1.f, 1.f, 1.f));
	visualizer::ShapeGenerator shape_gen = visualizer::ShapeGenerator(visualizer::SphereSpecification(2), 3.f).with_shape(visualizer::CubeSpecification(), 1.f);

	visualizer::Creation creation = visualizer::Creation(shape_gen)
		.with_quantity(2000)
		.with_position(pos_gen)
		.with_size(size_gen)
		.with_velocity(speed_gen);

	visualizer.create_entities(creation);

	visualizer::Query cube_query = visualizer::Query().with_shape(visualizer::ShapeSpecification(visualizer::CubeSpecification()));
	visualizer::EntityGroup cubes = visualizer.query_entities(cube_query);

	std::cout << "number of cubes: " << cubes.get_movables().size() << std::endl;

	visualizer::Query sphere_query = visualizer::Query().with_shape(visualizer::ShapeSpecification(visualizer::SphereSpecification(2)));
	visualizer::EntityGroup spheres = visualizer.query_entities(sphere_query);

	std::cout << "number of spheres: " << spheres.get_movables().size() << std::endl;

	visualizer.run();
	return 0;
}
