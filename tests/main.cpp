#include <iostream>

#include "Visualizer.hpp"
#include "entity/creation/Creation.hpp"
#include "entity/creation/VectorGenerator.hpp"
#include "entity/creation/ShapeGenerator.hpp"
#include "entity/EntityBuffer.hpp"
#include "shape/ShapeSpecification.hpp"
#include "shape/ShapeHeap.hpp"
#include "entity/queries/Query.hpp"
#include "entity/Movable.hpp"
#include "shape/ShapeType.hpp"
#include "entity/movement/GroupMovement.hpp"
#include "entity/movement/RandomAcceleration.hpp"
#include "entity/movement/SimpleDrag.hpp"
#include "entity/movement/RandomColor.hpp"
#include "entity/movement/SimpleColorDrag.hpp"
#include "entity/movement/StdColor.hpp"

#include <glm/glm.hpp>

int main() {
	visualizer::Visualizer::init();
	std::optional<visualizer::Visualizer> opt_visualizer = visualizer::Visualizer::create(800, 600, "Visualizer");
	if (!opt_visualizer) {
		std::cout << "Couldnt create visualizer" << std::endl;
		return 1;
	}
	visualizer::Visualizer visualizer = *opt_visualizer;

	visualizer::VectorGenerator pos_gen = visualizer::VectorGenerator().with_stddev(glm::vec3(0.1f, 0.1f, 0.1f));
	visualizer::VectorGenerator size_gen = visualizer::VectorGenerator(glm::vec3(0.05f, 0.05f, 0.05f)).with_stddev(glm::vec3(0.01f));
	visualizer::VectorGenerator speed_gen = visualizer::VectorGenerator().with_stddev(glm::vec3(1.f, 1.f, 1.f));
	visualizer::ShapeGenerator shape_gen = visualizer::ShapeGenerator(visualizer::SphereSpecification(2), 1.f).with_shape(visualizer::CubeSpecification(), 1.f);
	float color_brightness = 0.1f;
	float color_variance = 0.1f;
	visualizer::VectorGenerator color_gen = visualizer::VectorGenerator(glm::vec3(color_brightness, color_brightness, color_brightness*3))
		.with_stddev(glm::vec3(color_variance, color_variance, color_variance));;

	visualizer::Creation creation = visualizer::Creation(shape_gen, "main_group")
		.with_quantity(2000)
		.with_position(pos_gen)
		.with_size(size_gen)
		.with_velocity(speed_gen)
		.with_color(color_gen);

	visualizer.create_entities(creation);

	visualizer::Query cube_query = visualizer::Query().with_shape(visualizer::ShapeType::CUBE);
	visualizer::EntityReferences cubes = visualizer.query_entities(cube_query);

	visualizer::GroupMovement cube_flow_field((visualizer::RandomPaths()));
	visualizer::GroupMovement cube_circle((visualizer::Circle(glm::vec3(), 5.f)));
	visualizer::GroupMovement cube_plain((visualizer::PlainForce(0.001f)));
	visualizer::Movement cube_drag(new visualizer::SimpleDrag(0.3f));
	visualizer::Movement random_acceleation(new visualizer::RandomAcceleration(0.04f));
	visualizer::Movement color_drag(new visualizer::SimpleColorDrag(0.1f));
	visualizer::Movement std_color(new visualizer::StdColor(0.04f));

	for (visualizer::Movable* m : cubes)
	{
		m->add_movement(cube_drag);
		m->add_movement(color_drag);
		m->add_movement(std_color);
	}

	visualizer::Query sphere_query = visualizer::Query().with_shape(visualizer::ShapeType::SPHERE);
	visualizer::EntityReferences spheres = visualizer.query_entities(sphere_query);

	visualizer::Movement sphere_drag(new visualizer::SimpleDrag(0.3f));

	for (visualizer::Movable* m : spheres)
	{
		m->add_movement(sphere_drag);
		m->add_movement(color_drag);
		m->add_movement(std_color);
	}

	// Color Movements
	float b = 0.03f;
	float v = 0.03f;
	visualizer::Movement sphere_color_random(new visualizer::RandomColor(visualizer::VectorGenerator(glm::vec3(b*3, -b, -b)).with_stddev(glm::vec3(v, v, v))));
	visualizer::Movement cube_color_random(new visualizer::RandomColor(visualizer::VectorGenerator(glm::vec3(-b, b*3, -b)).with_stddev(glm::vec3(v, v, v))));

	// unsigned int counter = 0;

	while (!visualizer.should_close()) {
		/*
		if (counter == 0)
		{
			for (visualizer::Movable* m : cubes)
			{
				m->add_movement(random_acceleation);
				//m->add_movement(cube_color_random);
			}
			for (visualizer::Movable* m : spheres)
			{
				m->add_movement(random_acceleation);
				//m->add_movement(sphere_color_random);
			}
		}
		counter = (counter + 1) % 160;
		*/

		cube_circle.apply_to(&visualizer.get_entities());
		cube_plain.apply_to(&visualizer.get_entities());

		visualizer.tick();
		visualizer.render();
	}

	visualizer.close();
	return 0;
}
