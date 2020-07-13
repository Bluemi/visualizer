#ifndef __SHADER_CLASS__
#define __SHADER_CLASS__

#include <string>
#include <optional>

namespace visualizer {
	class Shader {
		public:
			static std::optional<Shader> from_file(const std::string& path, unsigned int shader_type);
			static std::optional<Shader> from_code(const std::string& code, unsigned int shader_type);

			Shader(unsigned int id, unsigned int shader_type);

			unsigned int get_shader_type() const;
			unsigned int get_id() const;

			void del() const;
		private:
			unsigned int _id;
			unsigned int _shader_type;
	};
}

#endif
