#ifndef PAINTBRUSH_H
#define PAINTBRUSH_H

#include "RGBColor.h"

/// @brief Struct that represents a tool used to draw. It contains an RGBColor and the thickness of the line that will be drawn if used.
struct PaintBrush {
	RGBColor color; 	/**< Color of the line.*/
	float thickness;	/**< Thickness of the line.*/

	/** Default constructor. Creates a PaintBrush with BLACK color and thickness 1.*/
	PaintBrush() { this->color = RGBColor(0,0,0); this->thickness = 1.0; }
	
	/** Parametric constructor. Creates a PaintBrush with @p color color and thickness @p thickness.
	*	@param color Color of the paintbrush.
	*	@param thickness Thickness of the paintbrush.
	*/
	PaintBrush(RGBColor color, float thickness) { this->color = color; this->thickness = thickness; }
};

#endif