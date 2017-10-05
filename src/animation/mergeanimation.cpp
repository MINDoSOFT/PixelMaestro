#include "mergeanimation.h"

namespace PixelMaestro {
	MergeAnimation::MergeAnimation(Colors::RGB* colors, uint8_t num_colors) : Animation(colors, num_colors) {
		type_ = AnimationType::Merge;
	}

	void MergeAnimation::update(Section* section) {
		if (orientation_ == Vertical) {
			for (uint16_t x = 0; x < section->get_dimensions()->x; x++) {
				mid_point_ = (section->get_dimensions()->y / 2) - 1;
				count_ = 0;

				// Note: COLUMN MUST BE A SIGNED INT IN ORDER TO ACCESS INDEX 0.
				for (int32_t y = mid_point_; y >= 0; y--) {
					section->set_one(x, y, get_color_at_index(count_ + cycle_index_));
					count_++;
				}

				/*
					Check for an odd number of Pixels.
					If so, set the center one to index 0.
				*/
				if (section->get_dimensions()->size() % 2 != 0) {
					mid_point_ += 1;
					section->set_one(x, mid_point_, &colors_[cycle_index_]);
				}

				mid_point_ += 1;

				// Go from the center to the last
				count_ = 0;
				for (uint16_t y = mid_point_; y < section->get_dimensions()->y; y++) {
					section->set_one(x, y, get_color_at_index(count_ + cycle_index_));
					count_++;
				}
			}
		}
		else {	// Horizontal
			for (uint16_t y = 0; y < section->get_dimensions()->y; y++) {
				mid_point_ = (section->get_dimensions()->x / 2) - 1;
				count_ = 0;

				// Note: ROW MUST BE A SIGNED INT IN ORDER TO ACCESS INDEX 0.
				for (int32_t x = mid_point_; x >= 0; x--) {
					section->set_one(x, y, get_color_at_index(count_ + cycle_index_));
					count_++;
				}

				/*
					Check for an odd number of Pixels.
					If so, set the center one to index 0.
				*/
				if (section->get_dimensions()->size() % 2 != 0) {
					mid_point_ += 1;
					section->set_one(mid_point_, y, &colors_[cycle_index_]);
				}

				mid_point_ += 1;

				// Go from the center to the last
				count_ = 0;
				for (uint16_t x = mid_point_; x < section->get_dimensions()->x; x++) {
					section->set_one(x, y, get_color_at_index(count_ + cycle_index_));
					count_++;
				}
			}
		}

		update_cycle(0, num_colors_);
	}

	MergeAnimation::~MergeAnimation() {}
}
