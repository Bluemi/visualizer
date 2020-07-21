#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Visualizer.hpp"
#include "shape/ShapeSpecification.hpp"
#include "shape/ShapeHeap.hpp"
#include "shape/ShapeType.hpp"
#include "ShaderProgram.hpp"
#include "shaders/Shaders.hpp"
#include "controller/Controller.hpp"
#include "controller/ResizeManager.hpp"
#include "controller/MouseManager.hpp"
#include "camera/Camera.hpp"


int main() {
	visualizer::init();

	int window_width = 800;
	int window_height = 600;

	visualizer::Camera camera;
	visualizer::Controller controller;

	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Visualizer", NULL, NULL);
	if (window == NULL) {
		std::cerr << "failed to create window" << std::endl;
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return 1;
	}

	glViewport(0, 0, window_width, window_height);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);
	std::optional<visualizer::ShaderProgram> opt_shader_program = visualizer::ShaderProgram::from_code(visualizer::Shaders::vertex_shader(), visualizer::Shaders::fragment_shader());
	if (!opt_shader_program) {
		std::cerr << "Failed to create shader program" << std::endl;
		return 1;
	}

	visualizer::ShaderProgram shader_program = *opt_shader_program;

	visualizer::resizing::init(window);

	// TODO
	// visualizer::MouseManager::init(window);
	// visualizer::MouseManager::add_controller(&_controller);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.05f, 0.07f, 0.08f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		controller.process_user_input(window, &camera);

		shader_program.use();
		shader_program.set_4fv("view", camera.get_look_at());
		glm::mat4 projection = glm::perspective(
			glm::radians(45.0f),
			static_cast<float>(window_width)/static_cast<float>(window_height),
			0.1f, 600.f
		);
		shader_program.set_4fv("projection", projection);

		// render object here

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	visualizer::close();
	return 0;
}
