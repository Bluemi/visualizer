#include "Shader.hpp"

#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <sstream>

namespace visualizer
{
	const unsigned int LOG_BUFFER_SIZE = 512;

	Shader Shader::from_file(const std::string& path, unsigned int shader_type)
	{
		std::string code;
		std::ifstream shader_file;

		shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			shader_file.open(path);
			std::stringstream stream;
			stream << shader_file.rdbuf();
			shader_file.close();
			code = stream.str();
		} catch (std::ifstream::failure e) {
			std::cout << "Error while reading shader: \"" << path << "\"" << std::endl;
		}

		unsigned int shader_id;
		int success;
		char infoLog[LOG_BUFFER_SIZE];

		const char* c = code.c_str();

		shader_id = glCreateShader(shader_type);
		glShaderSource(shader_id, 1, &c, NULL);
		glCompileShader(shader_id);

		// print compile errors
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader_id, LOG_BUFFER_SIZE, NULL, infoLog);
			std::cout << "ERROR: Compiling of shader: \"" << path << "\"" << std::endl;
		}

		return Shader(shader_id, shader_type);
	}

	Shader::Shader(unsigned int id, unsigned int shader_type)
		: _id(id), _shader_type(shader_type)
	{}

	unsigned int Shader::get_shader_type() const
	{
		return _shader_type;
	}

	unsigned int Shader::get_id() const
	{
		return _id;
	}

	void Shader::del() const
	{
		glDeleteShader(_id);
	}
}
