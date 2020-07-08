#include "Visualizer.hpp"

#include <iostream>
#include <cmath>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shape/ShapeInitializer.hpp"
#include "shape/ShapeHeap.hpp"
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
#include "shaders/Shaders.hpp"

namespace visualizer
{
	const static std::string VERTEX_SHADER_PATH = "src/shaders/vertex_shader.vs";
	const static std::string FRAGMENT_SHADER_PATH = "src/shaders/fragment_shader.fs";
	const static double DEFAULT_SPEED = 59.54188473881952259316;

	Visualizer::Visualizer(GLFWwindow* window, ShaderProgram shader_program, unsigned int window_width, unsigned int window_height)
		: _camera(glm::vec3(-5.f, 0.f, 0.f), 0.f, 0.f),
		  _shader_program(shader_program),
		  _window(window),
		  _last_frame_time(0.0),
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
		  _last_frame_time(v._last_frame_time),
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

	std::optional<Visualizer> Visualizer::create(unsigned int window_width, unsigned int window_height, const std::string& window_name)
	{
		GLFWwindow* window = glfwCreateWindow(window_width, window_height, window_name.c_str(), NULL, NULL);
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

		std::optional<ShaderProgram> opt_shader_program = ShaderProgram::from_code(Shaders::vertex_shader(), Shaders::fragment_shader());

		if (!opt_shader_program)
		{
			return {};
		}

		return Visualizer(window, *opt_shader_program, window_width, window_height);
	}

	double Visualizer::get_delta_time()
	{
		double delta_time = 0.0;
		if (_last_frame_time == 0.0)
		{
			glfwSetTime(0.0);
		} else {
			delta_time = glfwGetTime() - _last_frame_time;
		}
		_last_frame_time = glfwGetTime();
		return delta_time;
	}

	void Visualizer::tick()
	{
		const double speed = get_delta_time() * DEFAULT_SPEED;

		_controller.process_user_input(_window, &_camera);
		_camera.tick(speed);

		for (Movable& m : *this)
		{
			m.tick(speed);
		}
	}

	void Visualizer::render()
	{
		clear_window();
		_shader_program.use();
		_shader_program.set_4fv("view", _camera.get_look_at());
		glm::mat4 projection = glm::perspective(glm::radians(45.0f),
												_window_width/static_cast<float>(_window_height),
												0.1f, 600.f);
		_shader_program.set_4fv("projection", projection);

		for (const Movable& m : *this)
		{
			m.render(_shader_program);
		}

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}

	void Visualizer::create_entities(const Creation& creation)
	{
		_entities.insert(creation.create());
	}

	void Visualizer::close()
	{
		visualizer::MouseManager::clear();
		ResizeManager::clear_visualizers();
		g_shape_heap.close();

		glfwTerminate();
	}

	bool Visualizer::should_close() const
	{
		return glfwWindowShouldClose(_window);
	}

	double Visualizer::get_time() const
	{
		return glfwGetTime();
	}

	EntityBuffer& Visualizer::get_entities()
	{
		return _entities;
	}

	EntityIterator Visualizer::begin()
	{
		return EntityIterator(_entities.begin(),
							  _entities.begin()->second.begin());
	}

	EntityIterator Visualizer::end()
	{
		return EntityIterator(_entities.end(), {});
	}

	EntityReferences Visualizer::query_entities(const Query& query)
	{
		EntityReferences entity_references;
		if (query.get_groups().empty())
		{
			for (auto iter = _entities.begin(); iter != _entities.end(); ++iter)
				for (Movable& m : iter->second)
					if (query.entity_included(m))
						entity_references.push_back(&m);
		} else {
			for (const std::string& group : query.get_groups())
			{
				std::vector<Movable>& movables = _entities[group];
				for (Movable& m : movables)
					entity_references.push_back(&m);
			}
		}

		return entity_references;
	}

	void Visualizer::clear_window()
	{
			glClearColor(0.05f, 0.07f, 0.08f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}
