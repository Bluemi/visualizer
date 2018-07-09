#ifndef __CONTROLLER_CLASS__
#define __CONTROLLER_CLASS__

#include <map>
#include <vector>

struct GLFWwindow;

namespace visualizer
{
	class Camera;
	typedef unsigned int Key;

	class Controller
	{
		public:
			Controller();

			void mouse_callback(double x, double y);

			void process_user_input(GLFWwindow* window, Camera* camera);

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
			void process_camera(Camera* camera);

			std::map<Key, bool> _is_pressed;
			double x_change, y_change;
	};
}

#endif
