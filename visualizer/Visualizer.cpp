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
#include "controller/ResizeManager.hpp"
#include "entity/Entity.hpp"

namespace visualizer
{
	Visualizer::Visualizer()
		: _window_width(800), _window_height(600)
	{}

	void Visualizer::framebuffer_size_callback(GLFWwindow*, int width, int height)
	{
		_window_width = width;
		_window_height = height;
		glViewport(0, 0, width, height);
	}

	void Visualizer::init()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		_window = glfwCreateWindow(_window_width, _window_height, "LearnOpenGL", NULL, NULL);
		if (_window == NULL)
		{
			std::cout << "failed to create window" << std::endl;
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(_window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}

		glViewport(0, 0, _window_width, _window_height);
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		ResizeManager::init(_window);
		ResizeManager::add_visualizer(this);

		visualizer::MouseManager::init(_window);

		glEnable(GL_DEPTH_TEST);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void Visualizer::clear_window()
	{
			glClearColor(0.05f, 0.07f, 0.08f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}


	void Visualizer::run()
	{
		visualizer::Shape shape = visualizer::initialize::sphere(4, true);

		visualizer::ShaderProgram shader_program = visualizer::ShaderProgram::from_files(
				"visualizer/shaders/vertex_shader.vs",
				"visualizer/shaders/fragment_shader.fs");

		Entity entity(shape);

		Camera camera(glm::vec3(-5.f, 0.f, 0.f), 0.f, 0.f);

		_controller.instruct_camera(&camera);

		visualizer::MouseManager::add_controller(&_controller);
		clear_window();

		// render loop
		while (!glfwWindowShouldClose(_window))
		{
			_controller.process_user_input(_window);
			camera.tick();

			clear_window();

			shader_program.set_4fv("view", camera.get_look_at());

			glm::mat4 projection = glm::perspective(glm::radians(45.0f),
													_window_width/(float)_window_height,
													0.1f, 100.f);
			shader_program.set_4fv("projection", projection);

			entity.render(shader_program);

			glfwSwapBuffers(_window);
			glfwPollEvents();
		}

		visualizer::MouseManager::clear();
		_controller.clear_camera();
		ResizeManager::clear_visualizers();

		shape.free_buffers();
		glfwTerminate();
	}
}
