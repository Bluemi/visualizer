#include "visualizer/Visualizer.hpp"
#include "visualizer/entity/creation/Creation.hpp"
#include "visualizer/entity/creation/VectorGenerator.hpp"

#include <glm/glm.hpp>

int main() {
	visualizer::Visualizer visualizer;
	visualizer.init();

	visualizer::VectorGenerator pos_gen = visualizer::VectorGenerator().with_stddev(glm::vec3(5.f, 5.f, 5.f));
	visualizer::Creation creation = visualizer::Creation().with_quantity(30).with_position(pos_gen);

	visualizer.create_entities(creation);

	visualizer.run();
	return 0;
}
