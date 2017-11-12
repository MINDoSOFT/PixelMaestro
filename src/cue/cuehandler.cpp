/*
 * CueHandler - Base class for mapping Cues to PixelMaestro actions.
 */

#include "cuehandler.h"

namespace PixelMaestro {
	/**
	 * Returns the Section/Overlay corresponding to the given Section ID and Overlay level.
	 * @param section Index of the Section in the Maestro.
	 * @param overlay Overlay depth level.
	 * @return Matching Section/Overlay or nullptr if not found.
	 */
	Section* CueHandler::get_section(uint8_t section_id, uint8_t overlay_id) {

		Section* section = controller_->get_maestro()->get_section(section_id);

		/*
		 * Iterate until we hit the desired Overlay level.
		 * If there is no Overlay at that level, create it.
		 * Important: Overlays start at index 1, not 0!
		 */
		if (section != nullptr && overlay_id > 0) {
			for (uint8_t i = 0; i < overlay_id; i++) {
				if (section->get_overlay() != nullptr) {
					section = section->get_overlay()->section;
				}
				else {
					section = section->set_overlay()->section;
				}
			}
		}

		return section;
	}
}