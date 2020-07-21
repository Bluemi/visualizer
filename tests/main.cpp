#include <iostream>

#include "Visualizer.hpp"
#include "shape/ShapeSpecification.hpp"
#include "shape/ShapeHeap.hpp"
#include "shape/ShapeType.hpp"

#include <glm/glm.hpp>

int main() {
	visualizer::Visualizer::init();
	std::optional<visualizer::Visualizer> opt_visualizer = visualizer::Visualizer::create(800, 600, "Visualizer");
	if (!opt_visualizer) {
		std::cout << "Couldnt create visualizer" << std::endl;
		return 1;
	}
	visualizer::Visualizer visualizer = *opt_visualizer;

	while (!visualizer.should_close()) {
		visualizer.tick();
		visualizer.render();
	}

	visualizer.close();
	return 0;
}
