#include "visualizer.hpp"

#include <iostream>
#include <cmath>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shape/shape_initialization.hpp"
#include "shape/shape_heap.hpp"
#include "controller/MouseManager.hpp"
#include "controller/events.hpp"
#include "shaders/shaders.hpp"

namespace visualizer {
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
		resizing::init(_window);

		visualizer::MouseManager::init(_window);
		visualizer::MouseManager::add_controller(&_controller);
	}

	Visualizer::Visualizer(const Visualizer& v)
		: _controller(v._controller),
		  _camera(v._camera),
		  _shader_program(v._shader_program),
		  _window(v._window),
		  _last_frame_time(v._last_frame_time),
		  _window_width(v._window_width),
		  _window_height(v._window_height)
	{
		MouseManager::add_controller(&_controller);
	}

	Visualizer::~Visualizer() {
		MouseManager::remove_controller(&_controller);
	}

	// todo
	void Visualizer::framebuffer_size_callback(GLFWwindow*, int width, int height) {
		_window_width = width;
		_window_height = height;
		glViewport(0, 0, width, height);
	}

	void Visualizer::init() {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	}

	std::optional<Visualizer> Visualizer::create(unsigned int window_width, unsigned int window_height, const std::string& window_name) {
		GLFWwindow* window = glfwCreateWindow(window_width, window_height, window_name.c_str(), NULL, NULL);
		if (window == NULL) {
			std::cout << "failed to create window" << std::endl;
			glfwTerminate();
			return {};
		}

		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD" << std::endl;
			return {};
		}

		glViewport(0, 0, window_width, window_height);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glEnable(GL_DEPTH_TEST);
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		std::optional<ShaderProgram> opt_shader_program = ShaderProgram::from_code(Shaders::vertex_shader(), Shaders::fragment_shader());

		if (!opt_shader_program) {
			return {};
		}

		return Visualizer(window, *opt_shader_program, window_width, window_height);
	}

	double Visualizer::get_delta_time() {
		double delta_time = 0.0;
		if (_last_frame_time == 0.0) {
			glfwSetTime(0.0);
		} else {
			delta_time = glfwGetTime() - _last_frame_time;
		}
		_last_frame_time = glfwGetTime();
		return delta_time;
	}

	void Visualizer::tick() {
		const double speed = get_delta_time() * DEFAULT_SPEED;

		_controller.process_user_input(_window, &_camera);
		_camera.tick(speed);
	}

	void Visualizer::render() {
		clear_window();
		_shader_program.use();
		_shader_program.set_4fv("view", _camera.get_look_at());
		glm::mat4 projection = glm::perspective(glm::radians(45.0f),
												_window_width/static_cast<float>(_window_height),
												0.1f, 600.f);
		_shader_program.set_4fv("projection", projection);

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}

	void Visualizer::close() {
		visualizer::MouseManager::clear();
		g_shape_heap.close();

		glfwTerminate();
	}

	bool Visualizer::should_close() const {
		return glfwWindowShouldClose(_window);
	}

	double Visualizer::get_time() const {
		return glfwGetTime();
	}

	void Visualizer::clear_window() {
		glClearColor(0.05f, 0.07f, 0.08f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void init() {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	}

	void close() {
		glfwTerminate();
	}
}
