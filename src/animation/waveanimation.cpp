#include "waveanimation.h"

namespace PixelMaestro {
	WaveAnimation::WaveAnimation(Section& section) : Animation(section) {
		type_ = AnimationType::Wave;
		map();
	}

	int8_t WaveAnimation::get_skew() const {
		return skew_;
	}

	void WaveAnimation::set_skew(int8_t skew) {
		this->skew_ = skew;
		map();
	}

	void WaveAnimation::map() {
		for (uint16_t y = 0; y < section_.get_dimensions().y; y++) {
			for (uint16_t x = 0; x < section_.get_dimensions().x; x++) {
				uint8_t color_index;
				if (orientation_ == Orientation::Vertical || orientation_ == Orientation::VerticalFlipped) {
					color_index = y + (x * skew_);
				}
				else {	// Horizontal
					color_index = x + (y * skew_);
				}
				if (color_index == 255) color_index = 254;
				set_map_color_index(x, y, color_index);
			}
		}
	}

	void WaveAnimation::update() {
		update_cycle(0, palette_->get_num_colors());
	}
}
