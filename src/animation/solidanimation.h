#ifndef SOLIDANIMATION_H
#define SOLIDANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class SolidAnimation : public Animation {
		public:
			explicit SolidAnimation(Section* section);
			~SolidAnimation() = default;
			void update();
	};
}

#endif // SOLIDANIMATION_H
