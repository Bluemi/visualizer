#ifndef __SHADER_PROGRAM_CLASS__
#define __SHADER_PROGRAM_CLASS__

#include <string>
#include <optional>

#include <glm/glm.hpp>

namespace visualizer
{
	class Shader;

	class ShaderProgram
	{
		public:
			static std::optional<ShaderProgram> from_files(const std::string& vertex_shader_path, const std::string& fragment_shader_path);
			static std::optional<ShaderProgram> from_code(const std::string& vertex_shader_code, const std::string& fragment_shader_code);
			static std::optional<ShaderProgram> from_shaders(const Shader& vertex_shader, const Shader& fragment_shader);

			void use() const;
			unsigned int get_id() const;

			int get_uniform_location(const std::string& name) const;
			void set_bool(const std::string& name, bool value) const;
			void set_float(const std::string& name, float value) const;
			void set_int(const std::string& name, int value) const;
			void set_2f(const std::string& name, const glm::vec2& value) const;
			void set_3f(const std::string& name, const glm::vec3& value) const;
			void set_4f(const std::string& name, const glm::vec4& value) const;
			void set_4fv(const std::string& name, const glm::mat4& value) const;

		private:
			ShaderProgram(unsigned int id);

			// Program ID
			unsigned int _id;
	};
}

#endif
