#include "palette.h"

namespace PixelMaestro {
	/**
	 * Constructor. Sets the Palette's colors.
	 * @param colors Source color array.
	 * @param size Number of colors in the array.
	*/
	Palette::Palette(const std::vector<Colors::RGB> colors, uint8_t size) {
		set_colors(colors, size);
	}

	/**
	 * Copy constructor.
	 * @param other Other Palette to copy.
	 */
	Palette::Palette(const Palette &other) {
		set_colors(*(other.get_colors()), other.get_num_colors());
	}

	/**
	 * Copy assignment operator.
	 * @param other Other Palette to copy.
	 * @return New Palette.
	 */
	Palette& Palette::operator=(const Palette& other) {
		set_colors(*(other.get_colors()), other.get_num_colors());
		return *this;
	}

	/**
		Returns the color at the specified index.
		If the index exceeds the size of the color palette, the index wraps around to the start of the array and counts the remainder.
		For example, if the Section has 10 Pixels and 5 Colors, the Pixel at index 7 will use the color at index 2 (7 % 5 == 2).
		Used mainly to determine which color a Pixel should use during an animation based on where it is in the array.

		@param index Desired index.
		@return Color at the specified index.
	*/
	Colors::RGB& Palette::get_color_at_index(uint8_t index) const {
		if (index >= num_colors_) {
			return colors_->at(index % num_colors_);
		}
		else {
			return colors_->at(index);
		}
	}

	/**
	 * Returns the colors used in the Palette.
	 * @return Palette colors.
	 */
	std::vector<Colors::RGB>* Palette::get_colors() const {
		return colors_;
	}

	/**
	 * Returns the number of colors in the Palette.
	 * @return Palette size.
	 */
	uint8_t Palette::get_num_colors() const {
		return num_colors_;
	}

	/**
	 * Swaps the palette's color scheme.
	 * @param colors New colors.
	 * @param size New size.
	*/
	void Palette::set_colors(const std::vector<Colors::RGB> colors, uint8_t num_colors) {
		if (this->colors_ != NULL)
			this->colors_->clear();

		this->num_colors_ = num_colors;
		this->colors_ = new std::vector<Colors::RGB>(num_colors);
		for (uint8_t i = 0; i < num_colors; i++) {
			this->colors_->at(i) = colors[i];
		}
	}

	Palette::~Palette() {
		if (colors_ != NULL)
			colors_->clear();
	}
}
