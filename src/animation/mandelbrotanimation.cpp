#include "../utility.h"
#include "mandelbrotanimation.h"

namespace PixelMaestro {
	MandelbrotAnimation::MandelbrotAnimation(Section& section) : Animation(section) {
		type_ = AnimationType::Mandelbrot;
		map();
	}

	// FIXME: Fix Animations on Arduinos, likely caused by rounding errors.
	void MandelbrotAnimation::map() {
		uint8_t max_iterations = palette_->get_num_colors();
		if (orientation_ == Orientation::Horizontal || orientation_ == Orientation::HorizontalFlipped) {
			// Calculate the size/scale of the pattern
			double image_width = 4.0 / static_cast<double>(dimensions_.x);

			for (uint16_t y = 0; y < dimensions_.y; y++) {
				double c_imaginary = (y - center_.y) * image_width;
				for (uint16_t x = 0; x < dimensions_.x; x++) {
					double c_real = (x - center_.x) * image_width;

					double temp_x = 0;
					double temp_y = 0;
					iterations_ = 0;

					while ((temp_x * temp_x) + (temp_y * temp_y) < 4.0 && iterations_ < max_iterations) {
						double temp_x_2 = (temp_x * temp_x) - (temp_y * temp_y) + c_real;
						temp_y = (2.0 * temp_x * temp_y) + c_imaginary;
						temp_x = temp_x_2;
						iterations_++;
					}

					if (iterations_ < max_iterations) {
						set_map_color_index(x, y, iterations_);
					}
					else {
						set_map_color_index(x, y, 255);
					}
				}
			}
		}
		else { // Vertical orientation
			double image_width = 4.0 / dimensions_.y;

			for (uint16_t x = 0; x < dimensions_.x; x++) {
				double c_imaginary = (x - center_.x) * image_width;
				for (uint16_t y = 0; y < dimensions_.y; y++) {
					double c_real = (y - center_.y) * image_width;

					double temp_x = 0;
					double temp_y = 0;
					iterations_ = 0;

					while ((temp_y * temp_y) + (temp_x * temp_x) < 4 && iterations_ < max_iterations) {
						double temp_y_2	= (temp_y * temp_y) - (temp_x * temp_x) + c_real;
						temp_x = (2.0 * temp_x * temp_y) + c_imaginary;
						temp_y = temp_y_2;
						iterations_++;
					}

					if (iterations_ < max_iterations) {
						set_map_color_index(x, y, iterations_);
					}
					else {
						set_map_color_index(x, y, 255);
					}
				}
			}
		}
	}

	void MandelbrotAnimation::update() {
		update_cycle(0, palette_->get_num_colors());
	}
}
