#include "ColorsGenerateRandomColorTransition.h"
#include "../Utility.h"

namespace PixelMaestro {
	/**
	 * Constructor. Generates a new random Color.
	 * @param time Time to run the Transition.
	 * @param color Location to store the generated color.
	 */
	ColorsGenerateRandomColorTransition::ColorsGenerateRandomColorTransition(unsigned long time, Colors::RGB *color) : Transition(time) {
		this->color_ = color;
	}

	/**
	 * Constructor. Selects a random Color out of a selection of Colors.
	 * @param time Time to run the Transition.
	 * @param color Location to store the selected Color.
	 * @param selection Array to select a random color from.
	 * @param numOptions The number of Colors in the selection array.
	 */
	ColorsGenerateRandomColorTransition::ColorsGenerateRandomColorTransition(unsigned long time, Colors::RGB *color, Colors::RGB *selection, unsigned int numOptions) : Transition(time) {
		this->color_ = color;
		this->num_options_ = numOptions;
		this->selection_ = selection;
	}

	void ColorsGenerateRandomColorTransition::run() {
		if (this->selection_) {
			*this->color_ = this->selection_[Utility::rand() % this->num_options_];
		}
		else {
			*this->color_ = Colors::generateRandomColor();
		}
	}
}