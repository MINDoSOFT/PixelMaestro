#ifndef WAVEANIMATION_H
#define WAVEANIMATION_H

#include "mappedanimation.h"

namespace PixelMaestro {
	class WaveAnimation : public MappedAnimation {
		public:
			explicit WaveAnimation(Section* section);
			~WaveAnimation() = default;
			bool get_mirror() const;
			int8_t get_skew() const;
			void set_mirror(bool mirror);
			void set_skew(int8_t skew);
			void update();

		private:
			/// Tracks whether the orientation has changed.
			Animation::Orientation last_orientation_ = Orientation::Horizontal;

			/// Whether to mirror the wave across the x or y axis.
			bool mirror_ = false;

			/// The amount to offset each row (or column).
			int8_t skew_ = 0;

			void map();
	};
}

#endif // WAVEANIMATION_H
