#ifndef __SHADER_PROGRAM_CLASS__
#define __SHADER_PROGRAM_CLASS__

#include <string>

#include <glm/glm.hpp>

namespace visualizer
{
	class ShaderProgram
	{
		public:
			static ShaderProgram from_files(const std::string& vertex_shader_path, const std::string& fragment_shader_path);

			void use() const;
			unsigned int get_id() const;

			int get_uniform_location(const std::string& name) const;
			void set_bool(const std::string& name, bool value) const;
			void set_float(const std::string& name, float value) const;
			void set_int(const std::string& name, int value) const;
			void set_2f(const std::string& name, float x, float y) const;
			void set_4f(const std::string& name, float x, float y, float z, float w) const;
			void set_4fv(const std::string& name, const glm::mat4& value) const;

		private:
			ShaderProgram(unsigned int id);

			// Program ID
			unsigned int _id;
	};
}

#endif
