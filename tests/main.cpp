#include <iostream>

#include "Visualizer.hpp"
#include "entity/creation/Creation.hpp"
#include "entity/creation/VectorGenerator.hpp"
#include "entity/creation/ShapeGenerator.hpp"
#include "entity/EntityBuffer.hpp"
#include "shape/ShapeSpecification.hpp"
#include "shape/ShapeHeap.hpp"
#include "entity/queries/Query.hpp"
#include "shape/ShapeType.hpp"

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

	visualizer::Query cube_query = visualizer::Query().with_shape(visualizer::ShapeType::CUBE).with_position(visualizer::QuerySpace(glm::vec3(1.f, 0.f, 0.f), glm::vec3(2.f, 2.f, 2.f)));
	visualizer::EntityGroup cubes = visualizer.get_entities().query_group(cube_query);
	std::cout << "number of cubes: " << cubes.size() << std::endl;

	visualizer::Query sphere_query = visualizer::Query().with_shape(visualizer::ShapeType::SPHERE);
	visualizer::EntityGroup spheres = visualizer.get_entities().query_group(sphere_query);
	std::cout << "number of spheres: " << spheres.size() << std::endl;

	visualizer.run();
	return 0;
}
