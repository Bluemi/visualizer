#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "visualizer.hpp"
#include "shape/shape_specification.hpp"
#include "shape/shape.hpp"
#include "shape/shape_initialization.hpp"
#include "shaders/shaders.hpp"
#include "controller/events.hpp"


int main() {
	visualizer::init();

	int window_width = 800;
	int window_height = 600;

	visualizer::Camera camera;
	visualizer::Controller controller;

	GLFWwindow* window = visualizer::create_window(window_width, window_height);
	if (window == NULL) {
		std::cerr << "failed to create window" << std::endl;
		return 1;
	}

	std::optional<visualizer::ShaderProgram> opt_shader_program = visualizer::ShaderProgram::from_code(visualizer::Shaders::vertex_shader(), visualizer::Shaders::fragment_shader());
	if (!opt_shader_program) {
		std::cerr << "Failed to create shader program" << std::endl;
		return 1;
	}

	visualizer::Shape shape = visualizer::initialize::cube();

	visualizer::ShaderProgram shader_program = *opt_shader_program;

	visualizer::events::init(window);

	visualizer::events::register_resize_callback([&window_width, &window_height](int ww, int wh){ window_width=ww; window_height = wh; glViewport(0, 0, window_width, window_height); });
	visualizer::events::register_mouse_callback([&controller](double x, double y) { controller.mouse_callback(x, y); });

	glClearColor(0.05f, 0.07f, 0.08f, 1.0f);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		controller.process_user_input(window, &camera);
		camera.tick(0.1f);

		shader_program.use();
		shader_program.set_4fv("view", camera.get_look_at());
		glm::mat4 projection = glm::perspective(
			glm::radians(45.0f),
			static_cast<float>(window_width)/static_cast<float>(window_height),
			0.1f, 600.f
		);
		shader_program.set_4fv("projection", projection);
		shader_program.set_4fv("model", glm::mat4(1.f));
		shader_program.set_3f("color", glm::vec3(1.0, 0.0, 0.0));

		shape.bind();

		glDrawArrays(GL_TRIANGLES, 0, shape.get_number_vertices());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	visualizer::close();
	return 0;
}
