#ifndef CANVASTYPE_H
#define CANVASTYPE_H

namespace PixelMaestro {
	class CanvasType {
		public:
			/// Lists the types of Canvases available.
			enum Type {

				/// Traditional Canvas. Draws Pixels using the underlying Section Animation.
				AnimationCanvas,

				/// Draws Pixels using custom colors.
				ColorCanvas
			};
	};
}

#endif // CANVASTYPE_H