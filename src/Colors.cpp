/*
	Colors.cpp - Library for defining commonly used colors and methods for handling those colors.
*/

#include "Colors.h"
#include <stdlib.h>

namespace PixelMaestro {
	// Simple color set
	Colors::RGB Colors::RED 	= {255, 0, 0};
	Colors::RGB Colors::GREEN 	= {0, 255, 0};
	Colors::RGB Colors::BLUE 	= {0, 0, 255};
	Colors::RGB Colors::WHITE 	= {255, 255, 255};
	Colors::RGB Colors::BLACK 	= {0, 0, 0};

	// Extended color set
	Colors::RGB Colors::ORANGE 		= {255, 128, 0};
	Colors::RGB Colors::YELLOW 		= {255, 255, 0};
	Colors::RGB Colors::CHARTREUSE	= {128, 255, 0};
	Colors::RGB Colors::SPRING 		= {0, 255, 128};
	Colors::RGB Colors::CYAN 		= {0, 255, 255};
	Colors::RGB Colors::AZURE 		= {0, 128, 255};
	Colors::RGB Colors::VIOLET 		= {143, 0, 255};
	Colors::RGB Colors::MAGENTA 	= {255, 0, 255};
	Colors::RGB Colors::ROSE 		= {255, 0, 128};
	Colors::RGB Colors::INDIGO 		= {180, 0, 130};

	// Color collections
	Colors::RGB Colors::COLORWHEEL[12] = {
		Colors::RED,
		Colors::ORANGE,
		Colors::YELLOW,
		Colors::CHARTREUSE,
		Colors::GREEN,
		Colors::SPRING,
		Colors::CYAN,
		Colors::AZURE,
		Colors::BLUE,
		Colors::VIOLET,
		Colors::MAGENTA,
		Colors::ROSE
	};
	Colors::RGB Colors::RAINBOW[7] = {
		Colors::RED,
		Colors::ORANGE,
		Colors::YELLOW,
		Colors::GREEN,
		Colors::BLUE,
		Colors::INDIGO,
		Colors::VIOLET
	};

	/**
		Converts an HSV value to an RGB value.
		Courtesy of Elco Jacobs' ShiftPWM library (http://www.elcojacobs.com/shiftpwm/)

		@param hue The initial hue.
		@param sat The initial saturation.
		@param val The initial value.
	*/
	Colors::RGB Colors::HSVtoRGB(unsigned int hue, unsigned int sat, unsigned int val){
		Colors::RGB newColor;
		unsigned int accent = hue / 60;
		unsigned int bottom = ((255 - sat) * val)>>8;
		unsigned int top = val;
		unsigned char rising  = ((top - bottom) * (hue % 60)) / 60 + bottom;
		unsigned char falling = ((top - bottom) * (60 - hue % 60)) / 60 + bottom;

		switch(accent) {
			case 0:
				newColor.r = top;
				newColor.g = rising;
				newColor.b = bottom;
				break;
			case 1:
				newColor.r = falling;
				newColor.g = top;
				newColor.b = bottom;
				break;
			case 2:
				newColor.r = bottom;
				newColor.g = top;
				newColor.b = rising;
				break;
			case 3:
				newColor.r = bottom;
				newColor.g = falling;
				newColor.b = top;
				break;
			case 4:
				newColor.r = rising;
				newColor.g = bottom;
				newColor.b = top;
				break;
			case 5:
				newColor.r = top;
				newColor.g = bottom;
				newColor.b = falling;
				break;
		}
		return newColor;
	};

	/**
		Creates a randomly generated array of colors based off of a base color.

		@param newArray Array to populate.
		@param baseColor The initial color.
		@param numColors Number of colors to generate.
	*/
	void Colors::generateRandomColorArray(Colors::RGB newArray[], Colors::RGB baseColor, unsigned int numColors, float range) {
		for (unsigned int newColorIndex = 0; newColorIndex < numColors; newColorIndex++) {
			newArray[newColorIndex] = {
				(unsigned char)(baseColor.r > 0 ? baseColor.r - (unsigned char)(rand() % (unsigned char)(baseColor.r * range)) : 0),
				(unsigned char)(baseColor.g > 0 ? baseColor.g - (unsigned char)(rand() % (unsigned char)(baseColor.g * range)) : 0),
				(unsigned char)(baseColor.b > 0 ? baseColor.b - (unsigned char)(rand() % (unsigned char)(baseColor.b * range)) : 0)
			};
		}
	}

	/**
		Creates an array of colors that gradually merge from a base color to a target color.

		@param newArray Array to populate.
		@param baseColor The initial color.
		@param targetColor The target color.
		@param numColors Number of colors in the array.
		@param reverse If true, the second half of the array will transition from targetColor back to baseColor.
	*/
	void Colors::generateScalingColorArray(RGB newArray[], RGB baseColor, RGB targetColor, unsigned int numColors, bool reverse) {
		if (reverse) {
			numColors /= 2;
		}

		// Calculate the distance between each color.
		signed short step[] = {
			(signed short)((targetColor.r - baseColor.r) / (float)numColors),
			(signed short)((targetColor.g - baseColor.g) / (float)numColors),
			(signed short)((targetColor.b - baseColor.b) / (float)numColors)
		};

		// Apply the step distance to each index of the array.
		for (unsigned int i = 0; i < numColors; i++) {
			newArray[i].r =	baseColor.r + (step[0] * i);
			newArray[i].g = baseColor.g + (step[1] * i);
			newArray[i].b = baseColor.b + (step[2] * i);
		}

		if (reverse) {
			// Handle the middle color.
			newArray[numColors].r = baseColor.r + (step[0] * numColors);
			newArray[numColors].g = baseColor.g + (step[1] * numColors);
			newArray[numColors].b = baseColor.b + (step[2] * numColors);

			// Repeat the first half of the array in reverse for each remaining color.
			for (unsigned int i = numColors + 1; i < (numColors * 2); i++) {
				newArray[i].r = newArray[numColors - (i - numColors)].r;
				newArray[i].g = newArray[numColors - (i - numColors)].g;
				newArray[i].b = newArray[numColors - (i - numColors)].b;
			}
		}
	}

	/**
		Creates an array of colors that gradually merge from a base color to a target color.
		The threshold determines the difference between the target color and the base color.

		@param newArray Array to populate.
		@param baseColor The initial color.
		@param numColors Number of colors in the array.
		@param threshold The variation between the base color and the newly generated target color.
		@param reverse If true, the array will be doubled to transition from baseColor to targetColor, then back to baseColor.
	*/
	void Colors::generateScalingColorArray(RGB newArray[], RGB baseColor, unsigned int numColors, unsigned char threshold, bool reverse) {
		RGB newColor = {
			(unsigned char)(baseColor.r - threshold),
			(unsigned char)(baseColor.g - threshold),
			(unsigned char)(baseColor.b - threshold)
		};
		Colors::generateScalingColorArray(newArray, baseColor, newColor, numColors, reverse);
	}

	/**
		Mixes two colors.

		@param colorOne The first color to mix.
		@param colorTwo The second color to mix.
		@param mode The type of mixing to perform.
		@param alpha Color two alpha factor.
		@return The mixed color.
	*/
	Colors::RGB Colors::mixColors(RGB *colorOne, RGB *colorTwo, MixMode mode, float alpha) {
		Colors::RGB mixedColor;

		switch (mode) {
			case MixMode::ALPHA_BLENDING:
			{
				mixedColor.r = (alpha * colorTwo->r) + ((1 - alpha) * colorOne->r);
				mixedColor.g = (alpha * colorTwo->g) + ((1 - alpha) * colorOne->g);
				mixedColor.b = (alpha * colorTwo->b) + ((1 - alpha) * colorOne->b);
				break;
			}
			default:	// Normal blending
			{
				mixedColor.r = (colorOne->r + colorTwo->r) / 2;
				mixedColor.g = (colorOne->g + colorTwo->g) / 2;
				mixedColor.b = (colorOne->b + colorTwo->b) / 2;
			}
		};

		return mixedColor;
	}
}