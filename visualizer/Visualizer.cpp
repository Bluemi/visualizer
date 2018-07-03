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
#include "controller/MouseManager.hpp"
#include "controller/ResizeManager.hpp"
#include "entity/Movable.hpp"
#include "movement/SetSpeed.hpp"
#include "movement/GotoCamera.hpp"
#include "movement/SeekTargets.hpp"
#include "movement/SimpleDrag.hpp"
#include "movement/Circle.hpp"
#include "movement/RandomAcceleration.hpp"

namespace visualizer
{
	Visualizer::Visualizer()
		: _window_width(800), _window_height(600), _camera(glm::vec3(-5.f, 0.f, 0.f), 0.f, 0.f)
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

		_controller.instruct_camera(&_camera);

		visualizer::MouseManager::init(_window);
		visualizer::MouseManager::add_controller(&_controller);

		glEnable(GL_DEPTH_TEST);
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void Visualizer::clear_window()
	{
			glClearColor(0.05f, 0.07f, 0.08f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Visualizer::run()
	{
		visualizer::Shape sphere_shape = visualizer::initialize::sphere(4, true);
		visualizer::Shape cube_shape = visualizer::initialize::cube();

		visualizer::ShaderProgram shader_program(visualizer::ShaderProgram::from_files(
				"visualizer/shaders/vertex_shader.vs",
				"visualizer/shaders/fragment_shader.fs"));

		std::vector<Movable> movables;

		Movable m1(sphere_shape);
		m1.set_position(glm::vec3(0.f, 0.f, 0.f));
		m1.set_size(glm::vec3(0.1f, 0.1f, 0.1f));
		movables.push_back(m1);

		Movable m2(cube_shape);
		m2.set_position(glm::vec3(3.f, 0.f, 0.f));
		m2.set_size(glm::vec3(0.1f, 0.1f, 0.1f));
		movables.push_back(m2);

		Movable m3(sphere_shape);
		m3.set_position(glm::vec3(3.f, 0.f, 3.f));
		m3.set_size(glm::vec3(0.1f, 0.1f, 0.1f));
		movables.push_back(m3);

		Movable m4(cube_shape);
		m4.set_position(glm::vec3(0.f, 0.f, 3.f));
		m4.set_size(glm::vec3(0.1f, 0.1f, 0.1f));
		movables.push_back(m4);

		std::vector<Movable> targets = movables;

		// Movement movement(new SeekTargets(movables));
		// movable.add_movement(movement);

		// Movement goto_camera(new GotoCamera(&_camera));
		// movable.add_movement(goto_camera);

		for (Movable& m : movables)
		{
			Movement circle(new Circle(glm::vec3(1.5f, 0.f, 1.5f), 5.f));
			m.add_movement(circle);

			Movement drag(new SimpleDrag(0.3f));
			m.add_movement(drag);

			Movement random(new RandomAcceleration(0.2f, 30));
			m.add_movement(random);
		}

		clear_window();

		// render loop
		while (!glfwWindowShouldClose(_window))
		{
			for (Movable& m : movables)
			{
				m.tick();
			}

			_controller.process_user_input(_window);
			_camera.tick();

			clear_window();

			shader_program.set_4fv("view", _camera.get_look_at());

			glm::mat4 projection = glm::perspective(glm::radians(45.0f),
													_window_width/(float)_window_height,
													0.1f, 100.f);
			shader_program.set_4fv("projection", projection);

			for (Movable& m : movables)
			{
				m.render(shader_program);
			}

			glfwSwapBuffers(_window);
			glfwPollEvents();
		}

		visualizer::MouseManager::clear();
		_controller.clear_camera();
		ResizeManager::clear_visualizers();

		cube_shape.free_buffers();
		sphere_shape.free_buffers();
		glfwTerminate();
	}
}
