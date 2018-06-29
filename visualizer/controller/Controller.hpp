#ifndef __CONTROLLER_CLASS__
#define __CONTROLLER_CLASS__

#include <map>
#include <vector>

#include <GLFW/glfw3.h>

class Camera;

namespace visualizer
{
	typedef unsigned int KeyType;
	class Controller
	{
		public:
			Controller();
			Controller(Camera* camera);
			void instruct_camera(Camera* camera);
			void process_user_input(GLFWwindow* window);

			void key_pressed(GLFWwindow* window, KeyType key);
			void key_released(GLFWwindow* window, KeyType key);

			static const KeyType CAMERA_FORWARD_KEY;
			static const KeyType CAMERA_BACKWARD_KEY;
			static const KeyType CAMERA_LEFT_KEY;
			static const KeyType CAMERA_RIGHT_KEY;
			static const KeyType CLOSE_KEY;
		private:
			std::map<KeyType, bool> _is_pressed;
			Camera* _camera;
	};
}

#endif
