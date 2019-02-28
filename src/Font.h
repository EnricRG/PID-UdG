#ifndef FONT_H
#define FONT_H
#include <allegro5/allegro_font.h>
#include "RGBColor.h"
#include <string>

/** @defgroup font_defaults Window Defaults
*	When using fonts, there are some parameters that you can skip and the default values will be used instead. This are these parameters.
*	@{
*/

static const RGBColor DEFAULT_FONT_COLOR = BLACK;			///< Default color for the default font
static const size_t DEFAULT_FONT_SIZE = 12;					///< Default size for the default font
static const int DEFAULT_FONT_FLAGS = 0;					///< Default flags for the default font

/** @}*/

/// @brief Structure that stores the information of a text font.
/** When drawing text, inner libraries user formats that are less user friendly than others. This struct tries to simplify the usage of this fonts.
*/
struct Font {
	ALLEGRO_FONT* font;		/**< Pointer to the structure that holds the information of an Allegro font.*/
	RGBColor color;			/**< Color of the font.*/
	int size;				/**< Size of the font.*/
	
	//Font inicialization attributes
	std::string fontPath;	/**< Path of the font file.*/
	int flags;				/**< Flags of font initialization.*/

	/** Default constructor of a Font. It creates an "Invalid font" because you have to, at least, indicate a path to search for a font file.
	*/
	Font() { init("", RGBColor(), 0, 0); } //Invalid font
	
	/** Parametric constructor of a font.
	*	@param font_path The path where the Font source is.
	*	@param color Color of the Font. Its value is DEFAULT_FONT_COLOR by default.
	*	@param size Font size. Its value is DEFAULT_FONT_SIZE by default.
	*	@param flags Font flags. Its value is DEFAULT_FONT_FLAGS by default.
	*/
	Font(std::string font_path, RGBColor color = DEFAULT_FONT_COLOR, int size = DEFAULT_FONT_SIZE, int flags = DEFAULT_FONT_FLAGS) { init(font_path, color, size, flags); }	
	
	/** Destructor of the struct.
	*/
	~Font() { destroy(); }

	/** Copy constructor of the class. Takes a font as input
	*	@param f Target Font to copy.
	*/
	Font(const Font & f) { copy(f); }
	
	/** Assignment operator for the struct.
	*	@param f Target font of the assignment.
	*/
	Font& operator=(const Font & f) {
		if (this != &f) {
			destroy();
			copy(f);
		}
		return *this;
	}

	/** Checks validity of the Font.
	*	@return True if the Font is valid (usable), false otherwise.
	*/
	bool isValid() const { return font != NULL; }
	
	/** Checks invalidity of the Font.
	*	@return True if the Font is invalid (not usable), false otherwise.
	*/
	bool isInvalid() const { return !isValid(); }

	/** Initializes the struct.
	*	@param font_path Path where the Font source is.
	*	@param color Color of the Font.
	*	@param size Font size.
	*	@param flags Font initialization flags.
	*/
	void init(std::string font_path, RGBColor color, int size, int flags) {
		this->fontPath = font_path;
		this->color = color;
		this->size = size;
		this->flags = flags;
		if (fontPath != "") font = al_load_font(fontPath.c_str(), this->size, this->flags);
		else font = NULL;
	}

	/** Clears all dynamically allocated memory of the struct.
	*/
	void destroy() {
		al_destroy_font(font);
		font = NULL;
	}

	/** Copies the data of a given font into this font.
	*	@param f Target Font to copy.
	*/
	void copy(const Font & f) {
		init(f.fontPath, f.color, f.size, f.flags);
	}
};

#endif