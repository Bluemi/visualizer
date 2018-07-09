#include "Visualizer.hpp"

#include <iostream>
#include <cmath>
#include <string>


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "images/stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shape/ShapeInitializer.hpp"
#include "controller/MouseManager.hpp"
#include "controller/ResizeManager.hpp"
#include "entity/Movable.hpp"
#include "entity/movement/SetSpeed.hpp"
#include "entity/movement/GotoCamera.hpp"
#include "entity/movement/SeekTargets.hpp"
#include "entity/movement/SimpleDrag.hpp"
#include "entity/movement/Circle.hpp"
#include "entity/movement/RandomAcceleration.hpp"
#include "entity/creation/Creation.hpp"
#include "entity/queries/Query.hpp"

namespace visualizer
{
	const static std::string VERTEX_SHADER_PATH = "src/shaders/vertex_shader.vs";
	const static std::string FRAGMENT_SHADER_PATH = "src/shaders/fragment_shader.fs";

	Visualizer::Visualizer(GLFWwindow* window, unsigned int window_width, unsigned int window_height)
		: _camera(glm::vec3(-5.f, 0.f, 0.f), 0.f, 0.f),
		  _shader_program(ShaderProgram::from_files(VERTEX_SHADER_PATH,
													FRAGMENT_SHADER_PATH)),
		  _window(window),
		  _window_width(window_width),
		  _window_height(window_height)
	{
		ResizeManager::init(_window);
		ResizeManager::add_visualizer(this);

		visualizer::MouseManager::init(_window);
		visualizer::MouseManager::add_controller(&_controller);
	}

	Visualizer::Visualizer(const Visualizer& v)
		: _controller(v._controller),
		  _camera(v._camera),
		  _shader_program(v._shader_program),
		  _entities(v._entities),
		  _window(v._window),
		  _window_width(v._window_width),
		  _window_height(v._window_height)
	{
		ResizeManager::add_visualizer(this);
		MouseManager::add_controller(&_controller);
	}

	Visualizer::~Visualizer()
	{
		ResizeManager::remove_visualizer(this);
		MouseManager::remove_controller(&_controller);
	}

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
	}

	std::optional<Visualizer> Visualizer::create(unsigned int window_width, unsigned int window_height)
	{
		GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Visualizer", NULL, NULL);
		if (window == NULL)
		{
			std::cout << "failed to create window" << std::endl;
			glfwTerminate();
			return {};
		}

		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return {};
		}

		glViewport(0, 0, window_width, window_height);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glEnable(GL_DEPTH_TEST);
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		return Visualizer(window, window_width, window_height);
	}

	void Visualizer::clear_window()
	{
			glClearColor(0.05f, 0.07f, 0.08f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Visualizer::run()
	{
		for (Movable& m : _entities.get_movables())
		{
			Movement circle(new Circle(glm::vec3(), 5.f));
			m.add_movement(circle);

			Movement drag(new SimpleDrag(0.3f));
			m.add_movement(drag);

			Movement random(new RandomAcceleration(0.08f, 60));
			m.add_movement(random);
		}

		clear_window();

		// render loop
		while (!glfwWindowShouldClose(_window))
		{
			for (Movable& m : _entities.get_movables())
			{
				m.tick();
			}

			_controller.process_user_input(_window, &_camera);
			_camera.tick();

			clear_window();

			_shader_program.set_4fv("view", _camera.get_look_at());

			glm::mat4 projection = glm::perspective(glm::radians(45.0f),
													_window_width/(float)_window_height,
													0.1f, 100.f);
			_shader_program.set_4fv("projection", projection);

			for (Movable& m : _entities.get_movables())
			{
				m.render(_shader_program);
			}

			glfwSwapBuffers(_window);
			glfwPollEvents();
		}
	}

	void Visualizer::create_entities(const Creation& creation)
	{
		_entities = creation.create();
	}

	void Visualizer::close()
	{
		visualizer::MouseManager::clear();
		ResizeManager::clear_visualizers();

		glfwTerminate();
	}

	EntityBuffer& Visualizer::get_entities()
	{
		return _entities;
	}
}
