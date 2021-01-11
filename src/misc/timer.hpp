#ifndef __TIMER_CLASS__
#define __TIMER_CLASS__

namespace visualizer {
	class Timer {
		public:
			Timer();

			double restart();
			double get_time() const;
			static double get_global_time();
		private:
			double _offset;
	};
}

#endif
