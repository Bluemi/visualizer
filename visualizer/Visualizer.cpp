#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "images/stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>

#include "Visualizer.hpp"
#include "ShaderProgram.hpp"
#include "ShapeInitializer.hpp"
#include "camera/Camera.hpp"
#include "controller/MouseManager.hpp"

namespace visualizer
{
	Visualizer::Visualizer()
	{}

	void framebuffer_size_callback(GLFWwindow*, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	std::string vec_to_str(const glm::vec3& vec)
	{
		return "(" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + ")";
	}

	void Visualizer::run()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
		if (window == NULL)
		{
			std::cout << "failed to create window" << std::endl;
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}

		glViewport(0, 0, 800, 600);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  

		visualizer::MouseManager::init(window);

		visualizer::Shape shape = visualizer::initialize::sphere(4, true);
		shape.bind();

		visualizer::ShaderProgram shader_program = visualizer::ShaderProgram::from_files(
				"visualizer/shaders/vertex_shader.vs",
				"visualizer/shaders/fragment_shader.fs");

		shader_program.use();

		glEnable(GL_DEPTH_TEST);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glm::vec3 cubePosition = glm::vec3(0.0f,  0.0f,  0.0f);

		Camera camera(glm::vec3(-5.f, 0.f, 0.f), 0.f, 0.f);

		_controller.instruct_camera(&camera);

		visualizer::MouseManager::add_controller(&_controller);

		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), 800.f/600.f, 0.1f, 100.f);

		// render loop
		while (!glfwWindowShouldClose(window))
		{
			_controller.process_user_input(window);
			camera.tick();

			/*
			std::cout << "camera_position: " << vec_to_str(camera.get_position()) << std::endl;
			std::cout << "camera_direction: " << vec_to_str(camera.get_direction()) << std::endl;
			std::cout << "camera_right: " << vec_to_str(camera.get_right()) << std::endl;
			std::cout << "camera_top: " << vec_to_str(camera.get_top()) << std::endl;
			*/

			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glm::mat4 view = camera.get_look_at();

			shader_program.set_4fv("view", view);
			shader_program.set_4fv("projection", projection);


			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePosition);
			shader_program.set_4fv("model", model);

			glDrawArrays(GL_TRIANGLES, 0, shape.get_number_vertices());

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		visualizer::MouseManager::clear();

		shape.free_buffers();
		glfwTerminate();
	}
}
