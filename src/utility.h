#ifndef UTILITY_H
#define UTILITY_H

#include <stdint.h>

namespace PixelMaestro {
	class Utility {
		public:
			static uint32_t abs_int(int32_t val);
			static int32_t rand(int32_t max = 0);
			static float sqrt(float val);
			static uint32_t square(int16_t val);

		private:
			/// Initial RNG seed.
			static int32_t seed_;
	};
}

#endif // UTILITY_H
