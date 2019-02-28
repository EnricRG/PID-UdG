#ifndef RGBCOLOR_H
#define RGBCOLOR_H

#include <allegro5/allegro.h>

const unsigned char MAX_CHAR = 255;

/// @brief RGB color.
/** Struct that holds the information about an RGB color. Supports transparency.
*/
struct RGBColor {
	unsigned char r, /**< Red value of the color.*/
				  g, /**< Green value of the color.*/
				  b, /**< Blue value of the color.*/
				  a; /**< Alpha value of the color.*/

	/** Default constructor. The resulting color is full opaque white.
	*/
	RGBColor() { this->b = MAX_CHAR; this->g = MAX_CHAR; this->b = MAX_CHAR; a = MAX_CHAR; }
	
	/** Parametric constructor. Doesn't support transparencies and takes only the RGB values.
	*	@param r Red value of the new background color.
	*	@param g Green value of the new background color.
	*	@param b Blue value of the new background color.
	*/
	RGBColor(int r, int g, int b) { this->r = r; this->g = g; this->b = b; a = MAX_CHAR; } //Color without transparency (alpha = 255)
	
	/** Parametric constructor. This one support transparencies.
	*	@param r Red value of the new background color.
	*	@param g Green value of the new background color.
	*	@param b Blue value of the new background color.
	*	@param a Alpha value of the new background color (level of opacity: 0 means transparent, 255 means opaque).
	*/
	RGBColor(int r, int g, int b, int a) { this->r = r; this->g = g; this->b = b; this->a = a; } //Full rgba color

	/** Returns the color in a Allegro-readable format.
	*/
	ALLEGRO_COLOR toAllegroColor() const { return al_premul_rgba(r, g, b, a); }
};

const RGBColor WHITE(255, 255, 255);
const RGBColor BLACK(0, 0, 0);
const RGBColor RED(255, 0, 0);
const RGBColor GREEN(0, 255, 0);
const RGBColor BLUE(0, 0, 255);
const RGBColor YELLOW(255, 255, 0);
const RGBColor MAGENTA(255, 0, 255);
const RGBColor CIAN(0, 255, 255);
const RGBColor GRAY(127, 127, 127);
const RGBColor LIGHTGRAY(223, 223, 223);

#endif