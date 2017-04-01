/*
	Colors.cpp - Library for defining commonly used colors and methods for handling those colors.

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef COLORS_H
#define COLORS_H

namespace PixelMaestro {
	class Colors {

		private:
		public:
			/// Stores an RGB definition of a color.
			struct RGB {
				unsigned char r;	/// The red value of the color.
				unsigned char g;	/// The green value of the color.
				unsigned char b;	/// The blue value of the color.

				bool operator==(RGB colorTwo) {
					return r == colorTwo.r && g == colorTwo.g && b == colorTwo.b;
				}

				bool operator!=(RGB colorTwo) {
					return !operator==(colorTwo);
				}

				RGB operator+(RGB colorTwo) {
					return {
						(unsigned char)((r + colorTwo.r) % 255),
						(unsigned char)((g + colorTwo.g) % 255),
						(unsigned char)((b + colorTwo.b) % 255)
					};
				}

				RGB operator-(RGB colorTwo) {
					return {
						(unsigned char)((r - colorTwo.r) % 255),
						(unsigned char)((g - colorTwo.g) % 255),
						(unsigned char)((b - colorTwo.b) % 255)
					};
				}
			};

			/// Determines the blending algorithm used when mixing two colors.
			enum MixMode {
				NORMAL,			/// Simple 50/50 blending.
				ALPHA_BLENDING	/// Overlays Color 2 on top of Color 1 with a specified blend percentage.
			};

			// Basic color set
			static RGB RED;
			static RGB GREEN;
			static RGB BLUE;
			static RGB WHITE;
			static RGB BLACK;

			// Extended color set
			static RGB ORANGE;
			static RGB YELLOW;
			static RGB CHARTREUSE;
			static RGB SPRING;
			static RGB CYAN;
			static RGB AZURE;
			static RGB VIOLET;
			static RGB MAGENTA;
			static RGB ROSE;
			static RGB INDIGO;
			static RGB COLORWHEEL[];
			static RGB RAINBOW[];

			static RGB HSVtoRGB(unsigned int hue, unsigned int sat, unsigned int val);
			static void generateRandomColorArray(RGB newArray[], RGB baseColor, unsigned char numColors, float range = 1.0);
			static void generateScalingColorArray(RGB newArray[], RGB baseColor, RGB targetColor, unsigned char numColors, bool reverse = false);
			static void generateScalingColorArray(RGB newArray[], RGB baseColor, unsigned char numColors, unsigned char threshold, bool reverse = false);
			static RGB mixColors(RGB *colorOne, RGB *colorTwo, MixMode mode, float alpha = 0);
	};
}

#endif // COLORS_H
