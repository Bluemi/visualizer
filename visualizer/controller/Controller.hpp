#ifndef __CONTROLLER_CLASS__
#define __CONTROLLER_CLASS__

#include <map>
#include <vector>

#include <GLFW/glfw3.h>

namespace visualizer
{
	class Camera;
	typedef unsigned int Key;

	class Controller
	{
		public:
			Controller();
			Controller(Camera* camera);

			void mouse_callback(double x, double y);
			void instruct_camera(Camera* camera);
			void clear_camera();

			void process_user_input(GLFWwindow* window);
			void process_camera();

			void key_pressed(GLFWwindow* window, Key key);
			void key_released(GLFWwindow* window, Key key);

			static const Key CAMERA_FORWARD_KEY;
			static const Key CAMERA_BACKWARD_KEY;
			static const Key CAMERA_LEFT_KEY;
			static const Key CAMERA_RIGHT_KEY;
			static const Key CAMERA_TOP_KEY;
			static const Key CAMERA_BOTTOM_KEY;
			static const Key CLOSE_KEY;
		private:
			std::map<Key, bool> _is_pressed;
			Camera* _camera;
			double x_change, y_change;
	};
}

#endif
