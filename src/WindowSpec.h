#ifndef WINDOWSPEC_H
#define WINDOWSPEC_H

/// @brief Dimensions of a Window.
/** Stores the information about the width and height of a Window. Only that.
*/
struct WindowSpec {
	int width, 	/**< Width of the Window.*/
		height; /**< Height of the Window.*/

	/** Constructor of the struct.
	*	@param width Width of the Window.
	*	@param height Height of the Window.
	*/
	WindowSpec(int width, int height) { this->width = width; this->height = height; }
};

#endif