#include "../Section.h"
#include "SectionSetCycleIntervalTransition.h"

using namespace PixelMaestro;

namespace PixelMaestro {
	SectionSetCycleIntervalTransition::SectionSetCycleIntervalTransition(unsigned long time, Section *section, unsigned short interval, unsigned short pause) : Transition(time) {
		this->section_ = section;
		this->interval_ = interval;
		this->pause_ = pause;
	}

	void SectionSetCycleIntervalTransition::run() {
		this->section_->setCycleInterval(this->interval_, this->pause_);
	}
}