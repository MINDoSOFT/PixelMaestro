/*
 * DemoPreset.cpp - Demonstrates how to configure a Maestro in a preset (spoiler alert: it's exactly the same).
 * Displays the text "Hello world!" and alternates from black to white.
 */

#include "animation/cycleanimation.h"
#include "canvas/animationcanvas.h"
#include "canvas/fonts/font5x8.h"
#include "core/colors.h"
#include "demopreset.h"

namespace PixelMaestro {
	void DemoPreset::apply(Maestro* maestro) {
		Section* section = maestro->get_section(0);

		// FIXME: Animation not working for base Section
		section->set_animation(new CycleAnimation(new Colors::RGB[2] { Colors::BLACK, Colors::WHITE }, 2, 2500, 1000));

		Section::Overlay* overlay = section->add_overlay(Colors::MixMode::OVERLAY);
		// Since the Overlay mix mode ignores black, we pass a color that's almost-but-not-quite black.
		overlay->section->set_animation(new CycleAnimation(new Colors::RGB[2] { Colors::WHITE, {0, 0, 1} }, 2, 2500, 1000));

		Canvas* canvas = overlay->section->set_canvas(new AnimationCanvas(overlay->section));

		Font5x8* font = new Font5x8();
		canvas->draw_text(1, 1, font, "Hello world!");
		delete font;
	}
}
