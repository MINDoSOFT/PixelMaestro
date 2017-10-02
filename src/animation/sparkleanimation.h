#ifndef SPARKLEANIMATION_H
#define SPARKLEANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class SparkleAnimation : public Animation {
		public:
			SparkleAnimation(Colors::RGB* colors = nullptr, uint8_t num_colors = 0, uint16_t speed = 100, uint16_t pause = 0, uint8_t threshold = 25);
			~SparkleAnimation();
			uint8_t get_threshold();
			void set_threshold(uint8_t threshold);
			void update(Section* section);

		private:
			/**
			 * Threshold for activating a Pixel (0 - 100).
			 * The higher the threshold, the more likely a Pixel will be activated.
			 */
			uint8_t threshold_;
	};
}

#endif // SPARKLEANIMATION_H
