#include "animationcuehandler.h"
#include "cuecontroller.h"
#include "sectioncuehandler.h"

namespace PixelMaestro {
	void SectionCueHandler::add_canvas(uint8_t section_num, uint8_t overlay_num, CanvasType::Type canvas_type) {
		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::SectionHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::AddCanvas;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = canvas_type;

		controller_->assemble((uint8_t)Byte::OptionsByte);
	}

	void SectionCueHandler::add_overlay(uint8_t section_num, uint8_t overlay_num, Colors::MixMode mix_mode, uint8_t alpha) {
		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::SectionHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::AddOverlay;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = mix_mode;
		controller_->get_cue()[Byte::OptionsByte + 1] = alpha;

		controller_->assemble((uint8_t)Byte::OptionsByte + 2);
	}

	void SectionCueHandler::set_animation(uint8_t section_num, uint8_t overlay_num, Animation::Type animation_type, bool preserve_cycle_index, Colors::RGB* colors, uint8_t num_colors) {

		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::SectionHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::SetAnimation;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = (uint8_t)animation_type;
		controller_->get_cue()[Byte::OptionsByte + 1] = (uint8_t)preserve_cycle_index;
		controller_->get_cue()[Byte::OptionsByte + 2] = num_colors;

		uint8_t colors_index = Byte::OptionsByte + 3;
		for (uint8_t i = 0; i < num_colors; i++) {
			controller_->get_cue()[colors_index] = colors[i].r;
			colors_index++;
			controller_->get_cue()[colors_index] = colors[i].g;
			colors_index++;
			controller_->get_cue()[colors_index] = colors[i].b;
			colors_index++;
		}

		controller_->assemble(colors_index);
	}

	void SectionCueHandler::set_dimensions(uint8_t section_num, uint8_t overlay_num, uint16_t x, uint16_t y) {
		IntByteConvert x_byte = IntByteConvert(x);
		IntByteConvert y_byte = IntByteConvert(y);

		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::SectionHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::SetDimensions;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = x_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 1] = x_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 2] = y_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 3] = y_byte.converted_1;

		controller_->assemble((uint8_t)Byte::OptionsByte + 4);
	}

	void SectionCueHandler::run(uint8_t *cue) {
		Section* section = controller_->get_maestro()->get_section(cue[Byte::SectionByte]);

		for (uint8_t i = 0; i < cue[Byte::OverlayByte]; i++) {
			section = section->get_overlay()->section;
		}

		if (section == nullptr) return;

		switch ((Action)cue[Byte::ActionByte]) {
			case Action::AddCanvas:
				section->add_canvas(CanvasType::Type(cue[Byte::OptionsByte]));
				break;
			case Action::AddOverlay:
				section->add_overlay(Colors::MixMode(cue[Byte::OptionsByte]), cue[Byte::OptionsByte + 1]);
				break;
			case Action::SetAnimation:
				{
					uint8_t num_colors = cue[Byte::OptionsByte + 2];
					if (num_colors == 0) {
						return;
					}
					uint8_t colors_index = Byte::OptionsByte + 3;
					Colors::RGB colors[num_colors];
					for (uint8_t i = 0; i < num_colors; i++) {
						colors[i].r = cue[colors_index];
						colors_index++;
						colors[i].g = cue[colors_index];
						colors_index++;
						colors[i].b = cue[colors_index];
						colors_index++;
					}
					Animation* animation = AnimationCueHandler::initialize_animation(cue);
					if (animation != nullptr) {
						/*
						 * Potential memory leak with this and AnimationCue::initialize.
						 * Delete the Section's existing Animation before assigning a new one.
						 */
						delete section->get_animation();
						section->set_animation(animation, (bool)cue[Byte::OptionsByte + 1]);
						animation->set_colors(colors, num_colors);
					}
				}
				break;
			case Action::SetDimensions:
				{
					uint16_t x = IntByteConvert::byte_to_int(&cue[Byte::OptionsByte]);
					uint16_t y = IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 2]);
					section->set_dimensions(x, y);
				}
				break;
		}
	}

	SectionCueHandler::~SectionCueHandler() { }
}
