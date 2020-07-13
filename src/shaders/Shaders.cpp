#include "Shaders.hpp"

/*
 * This define is used to embed the shader code into the executable
 * without having to write the code inside a cpp/hpp file.
 *
 * It is used in the shader files.
 */
#define VISUALIZER_SHADER_STRINGIFY(x) #x

namespace visualizer {
	namespace Shaders {
		// The version prefix is excluded from the shader code,
		// because otherwise it is interpreted as precompiler directive.
		const std::string VERSION_PREFIX = "#version 330\n";

		const std::string vertex_shader() {
			std::string s =
			#include "vertex_shader.vs"
			;
			return VERSION_PREFIX + s;
		}

		const std::string fragment_shader() {
			std::string s =
			#include "fragment_shader.fs"
			;
			return VERSION_PREFIX + s;
		}
	}
}
