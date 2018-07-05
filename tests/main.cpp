#include "visualizer/Visualizer.hpp"
#include "visualizer/entity/creation/Creation.hpp"
#include "visualizer/entity/creation/VectorGenerator.hpp"

#include <glm/glm.hpp>

int main() {
	visualizer::Visualizer visualizer;
	visualizer.init();

	visualizer::VectorGenerator pos_gen = visualizer::VectorGenerator().with_stddev(glm::vec3(5.f, 5.f, 5.f));
	visualizer::VectorGenerator size_gen = visualizer::VectorGenerator(glm::vec3(0.05f, 0.05f, 0.05f));
	visualizer::VectorGenerator speed_gen = visualizer::VectorGenerator().with_stddev(glm::vec3(1.f, 1.f, 1.f));
	//visualizer::NumberGenerator<unsigned int> quantity_gen = visualizer::NumberGenerator<unsigned int>().with_min(10).with_max(20);
	visualizer::Creation creation = visualizer::Creation().with_quantity(1000).with_position(pos_gen).with_size(size_gen).with_velocity(speed_gen);

	visualizer.create_entities(creation);

	visualizer.run();
	return 0;
}
