/// @file
#ifndef WINDOW_H
#define WINDOW_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <deque>
#include <map>

#include "PaintBrush.h"
#include "Point2D.h"
#include "Drawable.h"
#include "Font.h"
#include "WindowSpec.h"
#include "Image.h"
#include "Event.h"
#include "Point2D.h"

#include <string>
#include <iostream>

class Turtle;

typedef std::string MapKey;									///< Defining the key that will be used in all maps of this library (a string).
typedef std::map<MapKey, Turtle> TurtleMap;					///< Defining the Turtle Map: a std::map which its components are std::strings (the keys) and Turtles (the elements).
typedef std::pair<MapKey, Turtle> TurtleMapElement;			///< Defining the Turtle Map Element: a pair with both a key as <EM>first</EM> and an element of the map (a Turtle) as <EM>second</EM>.
typedef std::map<MapKey, Font> FontMap;						///< Defining the Font Map: a std::map which its components are std::strings (the keys) and Fonts (the elements).
typedef std::pair<MapKey, Font> FontMapElement;				///< Defining the Font Map Element: a pair with both a key as <EM>first</EM> and an element of the map (a Font) as <EM>second</EM>.

static const float CORRECTION_FACTOR = 0.5; ///< Allegro uses hardware accelerated graphics, so pixels are not absolute, and they're mapped with floating point coordinates. Because of this, a pixel is lit only if its center is lit (x+0.5, y+0.5), and this is the correction factor to get to that point */			

/** @defgroup line_join Line Join Options
*	When drawing some figures, like polylines or polygons, you can choose the way lines join together (<EM>line_join</EM> parameter). This are the accepted types.
*	@image html LINE_JOIN.png
*	@image latex LINE_JOIN.eps
*	@{
*/

static const int LINE_JOIN_NONE = ALLEGRO_LINE_JOIN_NONE;	///< No line join. This is the default value of <EM>line_join</EM> if it is not indicated.
static const int LINE_JOIN_BEVEL = ALLEGRO_LINE_JOIN_BEVEL; ///< Basic join between the lines. Simply draws a line between the two most separated line ends and fills the triangle that forms between. See the figure for a detailed graphic representation.
static const int LINE_JOIN_ROUND = ALLEGRO_LINE_JOIN_ROUND; ///< Rounds the join between lines. Draws a filled circle with the center in the outermost intersection between the lines. See the figure for a detailed graphic representation.
static const int LINE_JOIN_MITER = ALLEGRO_LINE_JOIN_MITER;	///< Makes an angle joint of the two lines. You may choose the miter length (<EM>miter_limit</EM> parameter) to set the length of the miter. See the figure for a detailed graphic representation (note that there's a number next to <STRONG>MITER</STRONG> word, this is the <EM>miter_limit</EM> of that drawing).

/** @}*/

/** @defgroup line_cap Line Cap Options
*	When drawing polylines you can choose the way lines cap is drawn (<EM>line_cap</EM> parameter). This are the accepted types.
*	@image html LINE_CAP.png
*	@image latex LINE_CAP.eps
*	@{
*/
static const int LINE_CAP_NONE = ALLEGRO_LINE_CAP_NONE;		///< No line cap. This is the default value of <EM>line_cap</EM> if it is not indicated.
static const int LINE_CAP_SQUARE = ALLEGRO_LINE_CAP_SQUARE; ///< Lengthens the line so the circle (only for representation purposes, that circle is never drawn) at the end of the line is completely filled, without edge smoothing. See the figure for a detailed graphic representation.
static const int LINE_CAP_ROUND = ALLEGRO_LINE_CAP_ROUND;	///< Lengthens the line so the circle (only for representation purposes, that circle is never drawn) at the end of the line is completely filled, with edge smoothing so the circle is the only extra filled part. See the figure for a detailed graphic representation.
static const int LINE_CAP_TRIANGLE = ALLEGRO_LINE_CAP_TRIANGLE;	///< Lengthens the line drawing an isosceles triangle with base at the line cap and height the radius of the circle (only for representation purposes, that circle is never drawn). See the figure for a detailed graphic representation.
static const int LINE_CAP_CLOSED = ALLEGRO_LINE_CAP_CLOSED; ///< Joins the end of the last line with the start point of the first line. Is basically the same as drawing a polygon.

/** @}*/

/** @defgroup text_align Text Alignment Options
*	When drawing text to the screen, you can choose the way text is aligned (<EM>flags</EM> parameter at <EM>text</EM> calls). If no selection is made, TEXT_ALIGN_LEFT is taken as default option. 
*	@{
*/

static const int TEXT_ALIGN_CENTER = ALLEGRO_ALIGN_CENTER;	///< The text is centered towards the drawing point.
static const int TEXT_ALIGN_LEFT = ALLEGRO_ALIGN_LEFT;		///< The text is aligned to the left border of the bounding box of the text.
static const int TEXT_ALIGN_RIGHT = ALLEGRO_ALIGN_RIGHT;	///< The text is aligned to the right border of the bounding box of the text.

/** @}*/

/** @defgroup window_defaults Window Defaults
*	Window have some parameters that cannot be chosen, nor changed. This are that parameters.
*	@{
*/

static const MapKey DEFAULT_TURTLE_NAME = "Donatello";		///< The name of the default Turtle that's with you since the first time you declare a Window. This Turtle cannot be released
static const MapKey DEFAULT_FONT_NAME = "default";			///< The name of the default Font of the class. This font cannot be modified nor erased.

static const Point2D TURTLE_HOME(0, 0);						///< Default Turtle start position (Bottom left corner).

static const char * DEFAULT_FONT_PATH = "resources/OpenSans-Regular.ttf"; ///< The path from which the default font is loaded 
static const Font DEFAULT_FONT(DEFAULT_FONT_PATH, DEFAULT_FONT_COLOR, DEFAULT_FONT_SIZE, DEFAULT_FONT_FLAGS); ///< Declaration and construction of the default font, used as default parameter of some methods.

/** @}*/

/// @brief Mid-level interface class that allows you to access all the functionalities of the library.
/**	This is the main class of the library. It contains all the drawing methods, and encapsulates all the needed modules to operate the display and its features like 
*	the Turtles. Look for <EM>primitives</EM> or <EM>turtle drawing</EM> in documentation for more detail about drawing functionalities. It also allows you to store
*	some Fonts and access them by the name you choose. 
*/
class Window
{
public:
	//class constants
	static const int DEFAULT_WIDTH = 640;					///< Default Window width if not specified in the constructor.
	static const int DEFAULT_HEIGHT = 480;					///< Default Window height if not specified in the constructor.
	static const int DEFAULT_LOG_SIZE = 256;				///< Default Window log size. If not specified, this is the maximum number of primitive operations that the Window will log and redraw if needed.


	/** @defgroup window_ctors How to create a Window
	*	It's pretty straight forward. You simply declare and instantiate it with one of the constructors of the class and it's done, you can start drawing.
	*	@{
	*/

	/** Parametric constructor of the Window class. All parameters are optional, so if you choose to instantiate the object without parameters, default values will be used instead.
	*	@param width Pixel width of the screen. If empty, DEFAULT_WIDTH is assumed.
	*	@param height Pixel height of the screen. If empty, DEFAULT_HEIGHT is assumed.
	*	@param background_color RGBColor that will be used as background color. Its value is BLACK by default.
	*	@param drawing_color RGBcolor that will be used to draw the primitives and Turtle interaction with the screen. WHITE is used by default.
	*	@param line_width When drawing some figures, the width of the line can be chosen. Width 1 is used by default.
	*	@param in_radians By default, Window uses degrees to represent angles. If this parameter is true, the Window will represent angles in radians.
	*	@param f When building the Window object, you can choose the default font that will be used when printing text. You can add more fonts later, without having to delete the others. If empty, DEFAULT_FONT is used instead.
	*	@param log_size The size of the log can be adjusted by the user. By default, it's DEFAULT_LOG_SIZE.
	*/
	Window(int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT, RGBColor background_color = WHITE, RGBColor drawing_color = BLACK, double line_width = 1.0, bool in_radians = false, Font f = DEFAULT_FONT, size_t log_size = DEFAULT_LOG_SIZE);
	
	/** Same as the first constructor, but with an additional parameter, the Window title. When instantiated, a new window opens in your computer and shows the drawing screen. This window has a title, and can be specified with <EM>window_title</EM> parameter. Other parameters work as before.
	*	@param window_title A string that will be used as the title of the new window that shows up when a Window is instantiated.
	*	@param width Pixel width of the screen. If empty, DEFAULT_WIDTH is assumed.
	*	@param height Pixel height of the screen. If empty, DEFAULT_HEIGHT is assumed.
	*	@param background_color RGBColor that will be used as background color. Its value is BLACK by default.
	*	@param drawing_color RGBcolor that will be used to draw the primitives and Turtle interaction with the screen. WHITE is used by default.
	*	@param line_width When drawing some figures, the width of the line can be chosen. Width 1 is used by default.
	*	@param in_radians By default, Window uses degrees to represent angles. If this parameter is true, the Window will represent angles in radians.
	*	@param f When building the Window object, you can choose the default font that will be used when printing text. You can add more fonts later, without having to delete the others. If empty, DEFAULT_FONT is used instead.
	*	@param log_size The size of the log can be adjusted by the user. By default, it's DEFAULT_LOG_SIZE.
	*/
	Window(std::string window_title, int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT, RGBColor background_color = WHITE, RGBColor drawing_color = BLACK, double line_width = 1.0, bool in_radians = false, Font f = DEFAULT_FONT, size_t log_size = DEFAULT_LOG_SIZE);
	
	/** Copy constructor of this class. The new Window inherits the configuration of the older Window (basically makes a clone of the Window passed as parameter).
	*	@param w The reference Window to copy.
	*/
	Window(const Window & w);

	/** @}*/

	/** Destructor of the class*/
	~Window();

	/** Assignment operator of the class*/
	Window& operator=(const Window & w);

	//direct primitive methods
	
	/** @defgroup window_primitives Drawing Primitives
	*	This are all the methods that draw directly on the Window. With them you can draw a bunch of pretty standard figures that will allow you to create more complex ones.
	*	@{
	*/

	/** Draws a pixel at the x,y position. It can be slow, so if you want to draw some figures consider using another primitive.
	*	For example this code:
	*	@include pixel_1.cpp
	*	Would generate this output:
	*	@image html pixel.png
	*	@image latex pixel.eps
	*	@param x X coordinate.
	*	@param y Y coordinate.
	*	@param color Color used to draw.
	*/
	void pixel(float x, float y, RGBColor color);

	/** Draws a line between two points.
	*	For example this code:
	*	@include line_1.cpp
	*	Would generate this output:
	*	@image html line.png
	*	@image latex line.eps
	*	@param x1 X coordinate of the first point.
	*	@param y1 Y coordinate of the first point.
	*	@param x2 X coordinate of the second point.
	*	@param y2 Y coordinate of the second point.
	*	@param color Color used to draw the pixel.
	*	@param thickness Thickness of the line. Its value is <EM>1.0</EM> by default.
	*/
	void line(float x1, float y1, float x2, float y2, RGBColor color, float thickness = 1.0);

	/** Draws a triangle between three points.
	*	For example this code:
	*	@include triangle_1.cpp
	*	Would generate this output:
	*	@image html triangle.png
	*	@image latex triangle.eps
	*	@param x1 X coordinate of the first point.
	*	@param y1 Y coordinate of the first point.
	*	@param x2 X coordinate of the second point.
	*	@param y2 Y coordinate of the second point.
	*	@param x3 X coordinate of the third point.
	*	@param y3 Y coordinate of the third point.
	*	@param color Color used to draw the figure.
	*	@param thickness Thickness of the figure. Its value is <EM>1.0</EM> by default.
	*/
	void triangle(float x1, float y1, float x2, float y2, float x3, float y3, RGBColor color, float thickness = 1.0);

	/** Draws a filled triangle given its three vertices coordinates.
	*	For example this code:
	*	@include filled_triangle_1.cpp
	*	Would generate this output:
	*	@image html filled_triangle.png
	*	@image latex filled_triangle.eps
	*	@param x1 X coordinate of the first point.
	*	@param y1 Y coordinate of the first point.
	*	@param x2 X coordinate of the second point.
	*	@param y2 Y coordinate of the second point.
	*	@param x3 X coordinate of the third point.
	*	@param y3 Y coordinate of the third point.
	*	@param color Color used to draw the figure.
	*/
	void filled_triangle(float x1, float y1, float x2, float y2, float x3, float y3, RGBColor color);

	/** Draws a rectangle given its top left and bottom right corners' coordinates.
	*	For example this code:
	*	@include rectangle_1.cpp
	*	Would generate this output:
	*	@image html rectangle.png
	*	@image latex rectangle.eps
	*	@param x1 X coordinate of the top left corner.
	*	@param y1 Y coordinate of the top left corner.
	*	@param x2 X coordinate of the bottom right corner.
	*	@param y2 Y coordinate of the bottom right corner.
	*	@param color Color used to draw the figure.
	*	@param thickness Thickness of the line. Its value is <EM>1.0</EM> by default.
	*/
	void rectangle(float x1, float y1, float x2, float y2, RGBColor color, float thickness = 1.0);

	/** Draws a filled rectangle given its top left and bottom right corners' coordinates.
	*	For example this code:
	*	@include filled_rectangle_1.cpp
	*	Would generate this output:
	*	@image html filled_rectangle.png
	*	@image latex filled_rectangle.eps
	*	@param x1 X coordinate of the top left corner.
	*	@param y1 Y coordinate of the top left corner.
	*	@param x2 X coordinate of the bottom right corner.
	*	@param y2 Y coordinate of the bottom right corner.
	*	@param color Color used to draw the figure.
	*/
	void filled_rectangle(float x1, float y1, float x2, float y2, RGBColor color);

	/** Draws a rounded rectangle given its top left and bottom right corners' coordinates and its rounding radii.
	*	For example this code:
	*	@include rounded_rectangle_1.cpp
	*	Would generate this output:
	*	@image html rounded_rectangle.png
	*	@image latex rounded_rectangle.eps
	*	<strong>NOTE</strong>: When rounding the rectangle, an ellipse is used to draw the curves around the corners (see figure below). The <EM>rx</EM> and <EM>ry</EM> parameters are the radii of the ellipse.
	*	@image html border_radius.png
	*	@image latex border_radius.eps
	*	@param x1 X coordinate of the top left corner.
	*	@param y1 Y coordinate of the top left corner.
	*	@param x2 X coordinate of the bottom right corner.
	*	@param y2 Y coordinate of the bottom right corner.
	*	@param rx Horizontal radius of the rounding ellipse.
	*	@param ry Vertical radius of the rounding ellipse.
	*	@param color Color used to draw the figure.
	*	@param thickness Thickness of the line. It's value is <EM>1.0</EM> by default.
	*/
	void rounded_rectangle(float x1, float y1, float x2, float y2, float rx, float ry, RGBColor color, float thickness = 1.0);

	/** Draws a rounded rectangle given its top left and bottom right corners' coordinates and its rounding radii.
	*	For example this code:
	*	@include filled_rounded_rectangle_1.cpp
	*	Would generate this output:
	*	@image html rounded_rectangle.png
	*	@image latex rounded_rectangle.eps
	*	<strong>NOTE</strong>: When rounding the rectangle, an ellipse is used to draw the curves around the corners (see figure below). The <EM>rx</EM> and <EM>ry</EM> parameters are the radii of the ellipse.
	*	@image html border_radius.png
	*	@image latex border_radius.eps
	*	@param x1 X coordinate of the top left corner.
	*	@param y1 Y coordinate of the top left corner.
	*	@param x2 X coordinate of the bottom right corner.
	*	@param y2 Y coordinate of the bottom right corner.
	*	@param rx Horizontal radius of the rounding ellipse.
	*	@param ry Vertical radius of the rounding ellipse.
	*	@param color Color used to draw the figure.
	*/
	void filled_rounded_rectangle(float x1, float y1, float x2, float y2, float rx, float ry, RGBColor color);

	/** Draws a quadrilateral given its four vertices. 
	*	The quadrilateral is drawn as follows: a line connects first and second point, then a line connects second point and the third, then the third is connected to the fourth and finally a line connects fourth and first points. 
	*	For example this code:
	*	@include quadrilateral_1.cpp
	*	Would generate this output:
	*	@image html quadrilateral.png
	*	@image latex quadrilateral.eps
	*	@param x1 X coordinate of the first point.
	*	@param y1 Y coordinate of the first point.
	*	@param x2 X coordinate of the second point.
	*	@param y2 Y coordinate of the second point.
	*	@param x3 X coordinate of the third point.
	*	@param y3 Y coordinate of the third point.
	*	@param x4 X coordinate of the fourth point.
	*	@param y4 Y coordinate of the fourth point.
	*	@param color Color used to draw the edges.
	*	@param thickness Thickness of the edges. Its value is <EM>1.0</EM> by default.
	*/
	void quadrilateral(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, RGBColor color, float thickness = 1.0);

	/** Draws a filled quadrilateral given its four vertices.
	*	The quadrilateral is drawn as follows: a line connects first and second point, then a line connects second point and the third, then the third is connected to the fourth and finally a line connects fourth and first points.
	*	For example this code:
	*	@include filled_quadrilateral_1.cpp
	*	Would generate this output:
	*	@image html filled_quadrilateral.png
	*	@image latex filled_quadrilateral.eps
	*	@param x1 X coordinate of the first point.
	*	@param y1 Y coordinate of the first point.
	*	@param x2 X coordinate of the second point.
	*	@param y2 Y coordinate of the second point.
	*	@param x3 X coordinate of the third point.
	*	@param y3 Y coordinate of the third point.
	*	@param x4 X coordinate of the fourth point.
	*	@param y4 Y coordinate of the fourth point.
	*	@param color Color used to draw the edges.
	*/
	void filled_quadrilateral(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, RGBColor color);

	/** Draws an ellipse given its center's coordinates and its radii.
	*	For example this code:
	*	@include ellipse_1.cpp
	*	Would generate this output:
	*	@image html ellipse.png
	*	@image latex ellipse.eps
	*	@param cx X coordinate of the center of the ellipse.
	*	@param cy Y coordinate of the center of the ellipse.
	*	@param rx Horizontal radius of the ellipse.
	*	@param ry Vertical radius of the ellipse.
	*	@param color Color used to draw the figure.
	*	@param thickness Thickness of the line. Its value is <EM>1.0</EM> by default.
	*/
	void ellipse(float cx, float cy, float rx, float ry, RGBColor color, float thickness = 1.0);

	/** Draws a filled ellipse given its center's coordinates and its radii.
	*	For example this code:
	*	@include filled_ellipse_1.cpp
	*	Would generate this output:
	*	@image html filled_ellipse.png
	*	@image latex filled_ellipse.eps
	*	@param cx X coordinate of the center of the ellipse.
	*	@param cy Y coordinate of the center of the ellipse.
	*	@param rx Horizontal radius of the ellipse.
	*	@param ry Vertical radius of the ellipse.
	*	@param color Color used to draw the figure.
	*/
	void filled_ellipse(float cx, float cy, float rx, float ry, RGBColor color);

	/** Draws a circle given its center's coordinates and its radius.
	*	For example this code:
	*	@include circle_1.cpp
	*	Would generate this output:
	*	@image html circle.png
	*	@image latex circle.eps
	*	@param cx X coordinate of the center of the circle.
	*	@param cy Y coordinate of the center of the circle.
	*	@param r Radius of the circle.
	*	@param color Color used to draw the figure.
	*	@param thickness Thickness of the line. Its value is <EM>1.0</EM> by default.
	*/
	void circle(float cx, float cy, float r, RGBColor color, float thickness = 1.0);

	/** Draws a filled circle given its center's coordinates and its radius.
	*	For example this code:
	*	@include filled_circle_1.cpp
	*	Would generate this output:
	*	@image html filled_circle.png
	*	@image latex filled_circle.eps
	*	@param cx X coordinate of the center of the circle.
	*	@param cy Y coordinate of the center of the circle.
	*	@param r Radius of the circle.
	*	@param color Color used to draw the figure.
	*/
	void filled_circle(float cx, float cy, float r, RGBColor color);

	/** Draws an arc given its center's coordinates, its radius and the angle it describes. The angle is represented as the start point of the angle <EM>start_theta</EM>, and the angle increase <EM>delta_theta</EM>. This angle can be expressed in radians or degrees depending on the Window configuration (degrees by default).
	*	For example this code:
	*	@include arc_1.cpp
	*	Would generate this output:
	*	@image html arc.png
	*	@image latex arc.eps
	*	@param cx X coordinate of the center of the arc.
	*	@param cy Y coordinate of the center of the arc.
	*	@param r Radius of the arc.
	*	@param start_theta Start point of the angle.
	*	@param delta_theta Angle increase.
	*	@param color Color used to draw the figure.
	*	@param thickness Thickness of the line. Its value is <EM>1.0</EM> by default.
	*/
	void arc(float cx, float cy, float r, float start_theta, float delta_theta, RGBColor color, float thickness = 1.0);

	/** Draws an arc given its center's coordinates, its radius and the angle it describes. The angle is represented as the start point of the angle <EM>start_theta</EM>, and the angle increase <EM>delta_theta</EM>. This angle can be expressed in radians or degrees depending on the Window configuration (degrees by default).
	*	For example this code:
	*	@include elliptical_arc_1.cpp
	*	Would generate this output:
	*	@image html elliptical_arc.png
	*	@image latex elliptical_arc.eps
	*	@param cx X coordinate of the center of the arc.
	*	@param cy Y coordinate of the center of the arc.
	*	@param rx Horizontal radius of the arc.
	*	@param ry Vertical radius of the arc.
	*	@param start_theta Start point of the angle.
	*	@param delta_theta Angle increase.
	*	@param color Color used to draw the figure.
	*	@param thickness Thickness of the line. Its value is <EM>1.0</EM> by default.
	*/
	void elliptical_arc(float cx, float cy, float rx, float ry, float start_theta, float delta_theta, RGBColor color, float thickness = 1.0);

	/** Draws a pie slice given its center's coordinates, its radius and the angle it describes. The angle is represented as the start point of the angle <EM>start_theta</EM>, and the angle increase <EM>delta_theta</EM>. This angle can be expressed in radians or degrees depending on the Window configuration (degrees by default).
	*	You can think of it as a "closed arc", an arc which its outermost radii are drawn as well.
	*	For example this code:
	*	@include pieslice_1.cpp
	*	Would generate this output:
	*	@image html pie slice.png
	*	@image latex pie slice.eps
	*	@param cx X coordinate of the center of the pie slice.
	*	@param cy Y coordinate of the center of the pie slice.
	*	@param r Radius of the pie slice.
	*	@param start_theta Start point of the angle.
	*	@param delta_theta Angle increase.
	*	@param color Color used to draw the figure.
	*	@param thickness Thickness of the line. Its value is <EM>1.0</EM> by default.
	*/
	void pieslice(float cx, float cy, float r, float start_theta, float delta_theta, RGBColor color, float thickness = 1.0);

	/** Draws a filled pie slice given its center's coordinates, its radius and the angle it describes. The angle is represented as the start point of the angle <EM>start_theta</EM>, and the angle increase <EM>delta_theta</EM>. This angle can be expressed in radians or degrees depending on the Window configuration (degrees by default).
	*	You can think of it as a "filled arc".
	*	For example this code:
	*	@include filled_pieslice_1.cpp
	*	Would generate this output:
	*	@image html filled_pieslice.png
	*	@image latex filled_pieslice.eps
	*	@param cx X coordinate of the center of the pie slice.
	*	@param cy Y coordinate of the center of the pie slice.
	*	@param r Radius of the pie slice.
	*	@param start_theta Start point of the angle.
	*	@param delta_theta Angle increase.
	*	@param color Color used to draw the figure.
	*/
	void filled_pieslice(float cx, float cy, float r, float start_theta, float delta_theta, RGBColor color);

	/** Draws a Bézier spline given its 4 control points.
	*	For example this code:
	*	@include spline_1.cpp
	*	Would generate this output:
	*	@image html spline.png
	*	@image latex spline.eps
	*	@param points An array of X and Y coordinates describing the points of the spline.
	*	@param color Color used to draw the figure.
	*	@param thickness Thickness of the line. Its value is <EM>1.0</EM> by default.
	*/
	void spline(float points[8], RGBColor color, float thickness = 1.0);

	/** Draws a ribbon given its segments' start and end points and the number of points.
	*	For example this code:
	*	@include ribbon_1.cpp
	*	Would generate this output:
	*	@image html ribbon.png
	*	@image latex ribbon.eps
	*	@param points An array of X and Y coordinates describing the points of the ribbon.
	*	@param num_points The number of points (pairs of X and Y coordinates) that <EM>points</EM> contains.
	*	@param color Color used to draw the figure.
	*	@param thickness Thickness of the line. Its value is <EM>1.0</EM> by default.
	*	@pre <EM>num_points</EM> must be less or equal than the real <EM>points</EM> buffer length divided by 2.
	*/
	void ribbon(const float *points, int num_points, RGBColor color, float thickness = 1.0);

	/** @addtogroup text_operations 
	*	@{
	*/
	
	/** Puts a text into the screen. By default, the text is aligned to the left. Depending on the alignment, the point passed will represent different positions of the text box. 
	*	When aligned left, the point passed will be the top left corner of the text box. When aligned right, it will be the top right corner, and when aligned to the center, the point will represent the exact center of the text box.
	*	For example this code:
	*	@include text_1.cpp
	*	Would generate this output:
	*	@image html text.png
	*	@image latex text.eps
	*	@param font The font used to write the text.
	*	@param x X coordinate where the text will be drawn
	*	@param y Y coordinate where the text will be drawn.
	*	@param text The text that will be written.
	*	@param flags This parameter can be used to specify the alignment of the text. See @ref text_align for more details. Its value is <EM>0</EM> by default.
	*/
	void text(Font & font, float x, float y, std::string text, int flags = 0);

	/** Puts a text into the screen. By default, the text is aligned to the left. Depending on the alignment, the point passed will represent different positions of the text box.
	*	When aligned left, the point passed will be the top left corner of the text box. When aligned right, it will be the top right corner, and when aligned to the center, the point will represent the exact center of the text box. 
	*	For example this code:
	*	@include text_2.cpp
	*	Would generate this output:
	*	@image html text.png
	*	@image latex text.eps
	*	@param font_name The name of the font (stored inside Window) used to write the text. The function will throw if the font doesn't exist.
	*	@param x X coordinate where the text will be drawn
	*	@param y Y coordinate where the text will be drawn.
	*	@param text The text that will be written.
	*	@param flags This parameter can be used to specify the alignment of the text. See @ref text_align for more details. Its value is <EM>0</EM> by default.
	*	@pre The font name must be a valid name and the font must exist in Window, otherwise it will throw an exception.
	*/
	void text(std::string font_name, float x, float y, std::string text, int flags = 0);

	/** @}*/
	
	/** Draws a polyline on the screen. Similar to <EM>ribbon</EM>, but this call allows you to configure more parameters.
	*	For example this code:
	*	@include polyline_1.cpp
	*	Would generate this output:
	*	@image html polyline.png
	*	@image latex polyline.eps
	*	@param vertices An array of X and Y coordinates describing the vertices of the polyline.
	*	@param vertex_count The number of vertices (pairs of X and Y coordinates) that <EM>vertices</EM> contains.
	*	@param color Color used to draw the figure.
	*	@param thickness Thickness of the line. Its value is <EM>1.0</EM> by default.
	*	@param join_style The way the lines join together. See @ref line_join for more details. Its value is <EM>LINE_JOIN_NONE</EM> by default.
	*	@param cap_style The way the lines join together. See @ref line_cap for more details. Its value is <EM>LINE_CAP_NONE</EM> by default.
	*	@param miter_limit Size of the miter. See @ref line_join for more details. Its value is <EM>0</EM> by default.
	*	@pre <EM>vertex_count</EM> must be less or equal than the real <EM>vertices</EM> buffer length divided by 2.
	*/
	void polyline(const float* vertices, int vertex_count, RGBColor color, float thickness = 1.0, int join_style = LINE_JOIN_NONE, int cap_style = LINE_CAP_NONE, float miter_limit = 0);
	
	/** Draws a polygon on the screen. Similar to <EM>polyline</EM>, but joining the first point with the last one.
	*	For example this code:
	*	@include polygon_1.cpp
	*	Would generate this output:
	*	@image html polygon.png
	*	@image latex polygon.eps
	*	@param vertices An array of X and Y coordinates describing the vertices of the polygon.
	*	@param vertex_count The number of vertices (pairs of X and Y coordinates) that <EM>vertices</EM> contains.
	*	@param color Color used to draw the figure.
	*	@param thickness Thickness of the line. Its value is <EM>1.0</EM> by default.
	*	@param join_style The way the lines join together. See @ref line_join for more details. Its value is <EM>LINE_JOIN_NONE</EM> by default.
	*	@param miter_limit Size of the miter. See @ref line_join for more details. Its value is <EM>0</EM> by default.
	*	@pre <EM>vertex_count</EM> must be less or equal than the real <EM>vertices</EM> buffer length divided by 2.
	*/
	void polygon(const float *vertices, int vertex_count, RGBColor color, float thickness = 1.0, int join_style = LINE_JOIN_NONE, float miter_limit = 0);

	/** Draws a filled polygon on the screen. Note that when drawing a filled polygon you cannot use the @ref line_join modifiers.
	*	For example this code:
	*	@include filled_polygon_1.cpp
	*	Would generate this output:
	*	@image html filled_polygon.png
	*	@image latex polygon.eps
	*	@param vertices An array of X and Y coordinates describing the vertices of the polygon.
	*	@param vertex_count The number of vertices (pairs of X and Y coordinates) that <EM>vertices</EM> contains.
	*	@param color Color used to draw the figure.
	*	@pre <EM>vertex_count</EM> must be less or equal than the real <EM>vertices</EM> buffer length divided by 2.
	*/
	void filled_polygon(const float *vertices, int vertex_count, RGBColor color);

	/** Draws a filled polygon with holes inside it on the screen. The holes must not intersect with the polygon outline. Note that when drawing a filled polygon you cannot use the @ref line_join modifiers.
	*	This call is a little special, and the parameters have to be configured in a specific way (see precondition). Here's an example of how you have to do it
	*	@include filled_polygon_with_holes_1.cpp
	*	There are 7 vertices: four for an outer trapezoid in anti - clockwise order, and three more for an inner triangle in clockwise order. The outer main polygon uses vertices 0 to 3 (inclusive) and the hole uses vertices 4 to 6 (inclusive).
	*	This code would generate this output:
	*	@image html filled_polygon_with_holes.png
	*	@image latex filled_polygon_with_holes.eps
	*	@param vertices An array of X and Y coordinates describing the vertices of the polygon and also the vertices of the holes.
	*	@param vertex_counts The number of vertices (pairs of X and Y coordinates) that <EM>vertices</EM> contains.
	*	@param color Color used to draw the figure.
	*	@pre <EM>vertex_count</EM> must be a 0 terminated array, which the total sum of its elements must be less or equal than the real <EM>vertices</EM> buffer length divided by 2.
	*		To effectively draw this figure, points of the holes must be ordered in the reverse order of the filled polygon vertices.
	*/
	void filled_polygon_with_holes(const float *vertices, const int *vertex_counts, RGBColor color);

	//methods that use struct Point2D to represent X and Y coordinates

	/** Draws a pixel at the p position. It can be slow, so if you want to draw some figures consider using another primitive.
	*	For example this code:
	*	@include pixel_2.cpp
	*	Would generate this output:
	*	@image html pixel.png
	*	@image latex pixel.eps
	*	@param p The point where the pixel will be drawn.
	*	@param color Color used to draw.
	*/
	void pixel(Point2D p, RGBColor color);
	
	/** Draws a line between two points.
	*	For example this code:
	*	@include line_2.cpp
	*	Would generate this output:
	*	@image html line.png
	*	@image latex line.eps
	*	@param p1 coordinates of the first point.
	*	@param p2 coordinates of the second point.
	*	@param color Color used to draw the pixel.
	*	@param thickness Thickness of the line. Its value is <EM>1.0</EM> by default.
	*/
	void line(Point2D p1, Point2D p2, RGBColor color, float thickness = 1.0);
	
	/** Draws a triangle between three points.
	*	For example this code:
	*	@include triangle_2.cpp
	*	Would generate this output:
	*	@image html triangle.png
	*	@image latex triangle.eps
	*	@param p1 coordinates of the first point.
	*	@param p2 coordinates of the second point.
	*	@param p3 coordinates of the third point.
	*	@param color Color used to draw the line.
	*	@param thickness Thickness of the line. Its value is <EM>1.0</EM> by default.
	*/
	void triangle(Point2D p1, Point2D p2, Point2D p3, RGBColor color, float thickness = 1.0);
	
	/** Draws a filled triangle given its three vertices coordinates.
	*	For example this code:
	*	@include filled_triangle_2.cpp
	*	Would generate this output:
	*	@image html filled_triangle.png
	*	@image latex filled_triangle.eps
	*	@param p1 coordinates of the first point.
	*	@param p2 coordinates of the second point.
	*	@param p3 coordinates of the third point.
	*	@param color Color used to draw the figure.
	*/
	void filled_triangle(Point2D p1, Point2D p2, Point2D p3, RGBColor color);
	
	/** Draws a rectangle given its top left and bottom right corners' coordinates.
	*	For example this code:
	*	@include rectangle_2.cpp
	*	Would generate this output:
	*	@image html rectangle.png
	*	@image latex rectangle.eps
	*	@param p1 coordinates of the top left corner.
	*	@param p2 coordinates of the bottom right corner.
	*	@param color Color used to draw the figure.
	*	@param thickness Thickness of the line. Its value is <EM>1.0</EM> by default.
	*/
	void rectangle(Point2D p1, Point2D p2, RGBColor color, float thickness = 1.0);
	
	/** Draws a filled rectangle given its top left and bottom right corners' coordinates.
	*	For example this code:
	*	@include filled_rectangle_2.cpp
	*	Would generate this output:
	*	@image html filled_rectangle.png
	*	@image latex filled_rectangle.eps
	*	@param p1 coordinates of the top left corner.
	*	@param p2 coordinates of the bottom right corner.
	*	@param color Color used to draw the figure.
	*/
	void filled_rectangle(Point2D p1, Point2D p2, RGBColor color);
	
	/** Draws a rounded rectangle given its top left and bottom right corners' coordinates and its rounding radii.
	*	For example this code:
	*	@include rounded_rectangle_2.cpp
	*	Would generate this output:
	*	@image html rounded_rectangle.png
	*	@image latex rounded_rectangle.eps
	*	<strong>NOTE</strong>: When rounding the rectangle, an ellipse is used to draw the curves around the corners (see figure below). The <EM>rx</EM> and <EM>ry</EM> parameters are the radii of the ellipse.
	*	@image html border_radius.png
	*	@image latex border_radius.eps
	*	@param p1 coordinates of the top left corner.
	*	@param p2 coordinates of the bottom right corner.
	*	@param rx Horizontal radius of the rounding ellipse.
	*	@param ry Vertical radius of the rounding ellipse.
	*	@param color Color used to draw the figure.
	*	@param thickness Thickness of the line. Its value is <EM>1.0</EM> by default.
	*/
	void rounded_rectangle(Point2D p1, Point2D p2, float rx, float ry, RGBColor color, float thickness = 1.0);
	
	/** Draws a rounded rectangle given its top left and bottom right corners' coordinates and its rounding radii.
	*	For example this code:
	*	@include filled_rounded_rectangle_2.cpp
	*	Would generate this output:
	*	@image html rounded_rectangle.png
	*	@image latex rounded_rectangle.eps
	*	<strong>NOTE</strong>: When rounding the rectangle, an ellipse is used to draw the curves around the corners (see figure below). The <EM>rx</EM> and <EM>ry</EM> parameters are the radii of the ellipse.
	*	@image html border_radius.png
	*	@image latex border_radius.eps
	*	@param p1 coordinates of the top left corner.
	*	@param p2 coordinates of the bottom right corner.
	*	@param rx Horizontal radius of the rounding ellipse.
	*	@param ry Vertical radius of the rounding ellipse.
	*	@param color Color used to draw the figure.
	*/
	void filled_rounded_rectangle(Point2D p1, Point2D p2, float rx, float ry, RGBColor color);
	
	/** Draws a quadrilateral given its four vertices.
	*	The quadrilateral is drawn as follows: a line connects first and second point, then a line connects second point and the third, then the third is connected to the fourth and finally a line connects fourth and first points.
	*	For example this code:
	*	@include quadrilateral_2.cpp
	*	Would generate this output:
	*	@image html quadrilateral.png
	*	@image latex quadrilateral.eps
	*	@param p1 coordinates of the first point.
	*	@param p2 coordinates of the second point.
	*	@param p3 coordinates of the third point.
	*	@param p4 coordinates of the fourth point.
	*	@param color Color used to draw the edges.
	*	@param thickness Thickness of the edges. Its value is <EM>1.0</EM> by default.
	*/
	void quadrilateral(Point2D p1, Point2D p2, Point2D p3, Point2D p4, RGBColor color, float thickness = 1.0);

	/** Draws a filled quadrilateral given its four vertices.
	*	The quadrilateral is drawn as follows: a line connects first and second point, then a line connects second point and the third, then the third is connected to the fourth and finally a line connects fourth and first points.
	*	For example this code:
	*	@include filled_quadrilateral_2.cpp
	*	Would generate this output:
	*	@image html filled_quadrilateral.png
	*	@image latex filled_quadrilateral.eps
	*	@param p1 coordinates of the first point.
	*	@param p2 coordinates of the second point.
	*	@param p3 coordinates of the third point.
	*	@param p4 coordinates of the fourth point.
	*	@param color Color used to draw the edges.
	*/
	void filled_quadrilateral(Point2D p1, Point2D p2, Point2D p3, Point2D p4, RGBColor color);

	/** Draws an ellipse given its center's coordinates and its radii.
	*	For example this code:
	*	@include ellipse_2.cpp
	*	Would generate this output:
	*	@image html ellipse.png
	*	@image latex ellipse.eps
	*	@param c coordinates of the center of the ellipse.
	*	@param rx Horizontal radius of the ellipse.
	*	@param ry Vertical radius of the ellipse.
	*	@param color Color used to draw the figure.
	*	@param thickness Thickness of the line. Its value is <EM>1.0</EM> by default.
	*/
	void ellipse(Point2D c, float rx, float ry, RGBColor color, float thickness = 1.0);
	
	/** Draws a filled ellipse given its center's coordinates and its radii.
	*	For example this code:
	*	@include filled_ellipse_2.cpp
	*	Would generate this output:
	*	@image html filled_ellipse.png
	*	@image latex filled_ellipse.eps
	*	@param c coordinates of the center of the ellipse.
	*	@param rx Horizontal radius of the ellipse.
	*	@param ry Vertical radius of the ellipse.
	*	@param color Color used to draw the figure.
	*/
	void filled_ellipse(Point2D c, float rx, float ry, RGBColor color);
	
	/** Draws a circle given its center's coordinates and its radius.
	*	For example this code:
	*	@include circle_2.cpp
	*	Would generate this output:
	*	@image html circle.png
	*	@image latex circle.eps
	*	@param c coordinates of the center of the circle.
	*	@param r Radius of the circle.
	*	@param color Color used to draw the figure.
	*	@param thickness Thickness of the line. Its value is <EM>1.0</EM> by default.
	*/
	void circle(Point2D c, float r, RGBColor color, float thickness = 1.0);
	
	/** Draws a filled circle given its center's coordinates and its radius.
	*	For example this code:
	*	@include filled_circle_2.cpp
	*	Would generate this output:
	*	@image html filled_circle.png
	*	@image latex filled_circle.eps
	*	@param c coordinates of the center of the circle.
	*	@param r Radius of the circle.
	*	@param color Color used to draw the figure.
	*/
	void filled_circle(Point2D c, float r, RGBColor color);
	
	/** Draws an arc given its center's coordinates, its radius and the angle it describes. The angle is represented as the start point of the angle <EM>start_theta</EM>, and the angle increase <EM>delta_theta</EM>. This angle can be expressed in radians or degrees depending on the Window configuration (degrees by default).
	*	For example this code:
	*	@include arc_2.cpp
	*	Would generate this output:
	*	@image html arc.png
	*	@image latex arc.eps
	*	@param c coordinates of the center of the arc.
	*	@param r Radius of the arc.
	*	@param start_theta Start point of the angle.
	*	@param delta_theta Angle increase.
	*	@param color Color used to draw the figure.
	*	@param thickness Thickness of the line. Its value is <EM>1.0</EM> by default.
	*/
	void arc(Point2D c, float r, float start_theta, float delta_theta, RGBColor color, float thickness = 1.0);
	
	/** Draws an arc given its center's coordinates, its radius and the angle it describes. The angle is represented as the start point of the angle <EM>start_theta</EM>, and the angle increase <EM>delta_theta</EM>. This angle can be expressed in radians or degrees depending on the Window configuration (degrees by default).
	*	For example this code:
	*	@include elliptical_arc_2.cpp
	*	Would generate this output:
	*	@image html elliptical_arc.png
	*	@image latex elliptical_arc.eps
	*	@param c coordinates of the center of the arc.
	*	@param rx Horizontal radius of the arc.
	*	@param ry Vertical radius of the arc.
	*	@param start_theta Start point of the angle.
	*	@param delta_theta Angle increase.
	*	@param color Color used to draw the figure.
	*	@param thickness Thickness of the line. Its value is <EM>1.0</EM> by default.
	*/
	void elliptical_arc(Point2D c, float rx, float ry, float start_theta, float delta_theta, RGBColor color, float thickness = 1.0);
	
	/** Draws a pie slice given its center's coordinates, its radius and the angle it describes. The angle is represented as the start point of the angle <EM>start_theta</EM>, and the angle increase <EM>delta_theta</EM>. This angle can be expressed in radians or degrees depending on the Window configuration (degrees by default).
	*	You can think of it as a "closed arc", an arc which its outermost radii are drawn as well.
	*	For example this code:
	*	@include pieslice_2.cpp
	*	Would generate this output:
	*	@image html pie slice.png
	*	@image latex pie slice.eps
	*	@param c coordinates of the center of the pie slice.
	*	@param r Radius of the pie slice.
	*	@param start_theta Start point of the angle.
	*	@param delta_theta Angle increase.
	*	@param color Color used to draw the figure.
	*	@param thickness Thickness of the line. Its value is <EM>1.0</EM> by default.
	*/
	void pieslice(Point2D c, float r, float start_theta, float delta_theta, RGBColor color, float thickness = 1.0);
	
	/** Draws a filled pie slice given its center's coordinates, its radius and the angle it describes. The angle is represented as the start point of the angle <EM>start_theta</EM>, and the angle increase <EM>delta_theta</EM>. This angle can be expressed in radians or degrees depending on the Window configuration (degrees by default).
	*	You can think of it as a "filled arc".
	*	For example this code:
	*	@include filled_pieslice_2.cpp
	*	Would generate this output:
	*	@image html filled_pieslice.png
	*	@image latex filled_pieslice.eps
	*	@param c coordinates of the center of the pie slice.
	*	@param r Radius of the pie slice.
	*	@param start_theta Start point of the angle.
	*	@param delta_theta Angle increase.
	*	@param color Color used to draw the figure.
	*/
	void filled_pieslice(Point2D c, float r, float start_theta, float delta_theta, RGBColor color);
	
	/** Draws a Bézier spline given its 4 control points.
	*	For example this code:
	*	@include spline_2.cpp
	*	Would generate this output:
	*	@image html spline.png
	*	@image latex spline.eps
	*	@param points An array of coordinates describing the points of the spline.
	*	@param color Color used to draw the figure.
	*	@param thickness Thickness of the line. Its value is <EM>1.0</EM> by default.
	*/
	void spline(Point2D points[4], RGBColor color, float thickness = 1.0);
	
	/** Draws a ribbon given its segments' start and end points and the number of points.
	*	For example this code:
	*	@include ribbon_2.cpp
	*	Would generate this output:
	*	@image html ribbon.png
	*	@image latex ribbon.eps
	*	@param points An array of coordinates describing the points of the ribbon.
	*	@param num_points The number of points that <EM>points</EM> contains.
	*	@param color Color used to draw the figure.
	*	@param thickness Thickness of the line. Its value is <EM>1.0</EM> by default.
	*	@pre <EM>num_points</EM> must be less or equal than the real <EM>points</EM> buffer length.
	*/
	void ribbon(const Point2D *points, int num_points, RGBColor color, float thickness = 1.0);
	
	/** @addtogroup text_operations 
	*	@{
	*/
	
	/** Puts a text into the screen. By default, the text is aligned to the left. Depending on the alignment, the point passed will represent different positions of the text box. 
	*	When aligned left, the point passed will be the top left corner of the text box. When aligned right, it will be the top right corner, and when aligned to the center, the point will represent the exact center of the text box.
	*	For example this code:
	*	@include text_3.cpp
	*	Would generate this output:
	*	@image html text.png
	*	@image latex text.eps
	*	@param font The font used to write the text.
	*	@param p coordinates where the text will be drawn.
	*	@param text The text that will be written.
	*	@param flags This parameter can be used to specify the alignment of the text. See @ref text_align for more details. Its value is <EM>0</EM> by default.
	*/
	void text(Font & font, Point2D p, std::string text, int flags = 0);
	
	/** Puts a text into the screen. By default, the text is aligned to the left. Depending on the alignment, the point passed will represent different positions of the text box.
	*	When aligned left, the point passed will be the top left corner of the text box. When aligned right, it will be the top right corner, and when aligned to the center, the point will represent the exact center of the text box.
	*	For example this code:
	*	@include text_4.cpp
	*	Would generate this output:
	*	@image html text.png
	*	@image latex text.eps
	*	@param font_name The name of the font (stored inside Window) used to write the text. The function will throw if the font doesn't exist.
	*	@param p coordinates where the text will be drawn.
	*	@param text The text that will be written.
	*	@param flags This parameter can be used to specify the alignment of the text. See @ref text_align for more details. Its value is <EM>0</EM> by default.
	*	@pre The font name must be a valid name and the font must exist in Window, otherwise it will throw an exception.
	*/
	void text(std::string font_name, Point2D p, std::string text, int flags = 0);
	
	/** @}*/
	
	/** Draws a polyline on the screen. Similar to <EM>ribbon</EM>, but this call allows you to configure more parameters.
	*	For example this code:
	*	@include polyline_2.cpp
	*	Would generate this output:
	*	@image html polyline.png
	*	@image latex polyline.eps
	*	@param vertices An array of coordinates describing the vertices of the polyline.
	*	@param vertex_count The number of vertices that <EM>vertices</EM> contains.
	*	@param color Color used to draw the figure.
	*	@param thickness Thickness of the line. Its value is <EM>1.0</EM> by default.
	*	@param join_style The way the lines join together. See @ref line_join for more details. Its value is <EM>LINE_JOIN_NONE</EM> by default.
	*	@param cap_style The way the lines join together. See @ref line_cap for more details. Its value is <EM>LINE_CAP_NONE</EM> by default.
	*	@param miter_limit Size of the miter. See @ref line_join for more details. Its value is <EM>0</EM> by default.
	*	@pre <EM>vertex_count</EM> must be less or equal than the real <EM>vertices</EM> buffer length.
	*/
	void polyline(const Point2D *vertices, int vertex_count, RGBColor color, float thickness = 1.0, int join_style = LINE_JOIN_NONE, int cap_style = LINE_CAP_NONE, float miter_limit = 0);
	
	/** Draws a polygon on the screen. Similar to <EM>polyline</EM>, but joining the first point with the last one.
	*	For example this code:
	*	@include polygon_2.cpp
	*	Would generate this output:
	*	@image html polygon.png
	*	@image latex polygon.eps
	*	@param vertices An array of coordinates describing the vertices of the polygon.
	*	@param vertex_count The number of vertices that <EM>vertices</EM> contains.
	*	@param color Color used to draw the figure.
	*	@param thickness Thickness of the line. Its value is <EM>1.0</EM> by default.
	*	@param join_style The way the lines join together. See @ref line_join for more details. Its value is <EM>LINE_JOIN_NONE</EM> by default.
	*	@param miter_limit Size of the miter. See @ref line_join for more details. Its value is <EM>0</EM> by default.
	*	@pre <EM>vertex_count</EM> must be less or equal than the real <EM>vertices</EM> buffer length.
	*/
	void polygon(const Point2D *vertices, int vertex_count, RGBColor color, float thickness = 1.0, int join_style = LINE_JOIN_NONE, float miter_limit = 0);
	
	/** Draws a filled polygon on the screen. Note that when drawing a filled polygon you cannot use the @ref line_join modifiers.
	*	For example this code:
	*	@include filled_polygon_2.cpp
	*	Would generate this output:
	*	@image html filled_polygon.png
	*	@image latex polygon.eps
	*	@param vertices An array of coordinates describing the vertices of the polygon.
	*	@param vertex_count The number of vertices (pairs of X and Y coordinates) that <EM>vertices</EM> contains.
	*	@param color Color used to draw the figure.
	*	@pre <EM>vertex_count</EM> must be less or equal than the real <EM>vertices</EM> buffer length.
	*/
	void filled_polygon(const Point2D *vertices, int vertex_count, RGBColor color);
	
	/** Draws a filled polygon with holes inside it on the screen. The holes must not intersect with the polygon outline. Note that when drawing a filled polygon you cannot use the @ref line_join modifiers.
	*	This call is a little special, and the parameters have to be configured in a specific way (see precondition). Here's an example of how you have to do it
	*	@include filled_polygon_with_holes_2.cpp
	*	There are 7 vertices: four for an outer trapezoid in anti - clockwise order, and three more for an inner triangle in clockwise order. The outer main polygon uses vertices 0 to 3 (inclusive) and the hole uses vertices 4 to 6 (inclusive).
	*	This code would generate this output:
	*	@image html filled_polygon_with_holes.png
	*	@image latex filled_polygon_with_holes.eps
	*	@param vertices An array of X and Y coordinates describing the vertices of the polygon and also the vertices of the holes.
	*	@param vertex_counts The number of vertices (pairs of X and Y coordinates) that <EM>vertices</EM> contains.
	*	@param color Color used to draw the figure.
	*	@pre <EM>vertex_count</EM> must be a 0 terminated array, which the total sum of its elements must be less or equal than the real <EM>vertices</EM> buffer length.
	*		To effectively draw this figure, points of the holes must be ordered in the reverse order of the filled polygon vertices.
	*/
	void filled_polygon_with_holes(const Point2D *vertices, const int *vertex_counts, RGBColor color);

	//same as the first primitive methods, but using class settings to draw
	
	/** Draws a pixel at the x,y position. This call uses the PaintBrush of the Window to draw, if needed. It can be slow, so if you want to draw some figures consider using another primitive.
	*	For example this code:
	*	@include pixel_3.cpp
	*	Would generate this output:
	*	@image html pixel.png
	*	@image latex pixel.eps
	*	@param x X coordinate.
	*	@param y Y coordinate.
	*/
	void pixel(float x, float y);
	
	/** Draws a line between two points. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include line_3.cpp
	*	Would generate this output:
	*	@image html line.png
	*	@image latex line.eps
	*	@param x1 X coordinate of the first point.
	*	@param y1 Y coordinate of the first point.
	*	@param x2 X coordinate of the second point.
	*	@param y2 Y coordinate of the second point.
	*/
	void line(float x1, float y1, float x2, float y2);
	
	/** Draws a triangle between three points. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include triangle_3.cpp
	*	Would generate this output:
	*	@image html triangle.png
	*	@image latex triangle.eps
	*	@param x1 X coordinate of the first point.
	*	@param y1 Y coordinate of the first point.
	*	@param x2 X coordinate of the second point.
	*	@param y2 Y coordinate of the second point.
	*	@param x3 X coordinate of the third point.
	*	@param y3 Y coordinate of the third point.
	*/
	void triangle(float x1, float y1, float x2, float y2, float x3, float y3);
	
	/** Draws a filled triangle given its three vertices coordinates. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include filled_triangle_3.cpp
	*	Would generate this output:
	*	@image html filled_triangle.png
	*	@image latex filled_triangle.eps
	*	@param x1 X coordinate of the first point.
	*	@param y1 Y coordinate of the first point.
	*	@param x2 X coordinate of the second point.
	*	@param y2 Y coordinate of the second point.
	*	@param x3 X coordinate of the third point.
	*	@param y3 Y coordinate of the third point.
	*/
	void filled_triangle(float x1, float y1, float x2, float y2, float x3, float y3);
	
	/** Draws a rectangle given its top left and bottom right corners' coordinates. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include rectangle_3.cpp
	*	Would generate this output:
	*	@image html rectangle.png
	*	@image latex rectangle.eps
	*	@param x1 X coordinate of the top left corner.
	*	@param y1 Y coordinate of the top left corner.
	*	@param x2 X coordinate of the bottom right corner.
	*	@param y2 Y coordinate of the bottom right corner.
	*/
	void rectangle(float x1, float y1, float x2, float y2);
	
	/** Draws a filled rectangle given its top left and bottom right corners' coordinates. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include filled_rectangle_3.cpp
	*	Would generate this output:
	*	@image html filled_rectangle.png
	*	@image latex filled_rectangle.eps
	*	@param x1 X coordinate of the top left corner.
	*	@param y1 Y coordinate of the top left corner.
	*	@param x2 X coordinate of the bottom right corner.
	*	@param y2 Y coordinate of the bottom right corner.
	*/
	void filled_rectangle(float x1, float y1, float x2, float y2);
	
	/** Draws a rounded rectangle given its top left and bottom right corners' coordinates and its rounding radii. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include rounded_rectangle_3.cpp
	*	Would generate this output:
	*	@image html rounded_rectangle.png
	*	@image latex rounded_rectangle.eps
	*	<strong>NOTE</strong>: When rounding the rectangle, an ellipse is used to draw the curves around the corners (see figure below). The <EM>rx</EM> and <EM>ry</EM> parameters are the radii of the ellipse.
	*	@image html border_radius.png
	*	@image latex border_radius.eps
	*	@param x1 X coordinate of the top left corner.
	*	@param y1 Y coordinate of the top left corner.
	*	@param x2 X coordinate of the bottom right corner.
	*	@param y2 Y coordinate of the bottom right corner.
	*	@param rx Horizontal radius of the rounding ellipse.
	*	@param ry Vertical radius of the rounding ellipse.
	*/
	void rounded_rectangle(float x1, float y1, float x2, float y2, float rx, float ry);
	
	/** Draws a rounded rectangle given its top left and bottom right corners' coordinates and its rounding radii. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include filled_rounded_rectangle_3.cpp
	*	Would generate this output:
	*	@image html rounded_rectangle.png
	*	@image latex rounded_rectangle.eps
	*	<strong>NOTE</strong>: When rounding the rectangle, an ellipse is used to draw the curves around the corners (see figure below). The <EM>rx</EM> and <EM>ry</EM> parameters are the radii of the ellipse.
	*	@image html border_radius.png
	*	@image latex border_radius.eps
	*	@param x1 X coordinate of the top left corner.
	*	@param y1 Y coordinate of the top left corner.
	*	@param x2 X coordinate of the bottom right corner.
	*	@param y2 Y coordinate of the bottom right corner.
	*	@param rx Horizontal radius of the rounding ellipse.
	*	@param ry Vertical radius of the rounding ellipse.
	*/
	void filled_rounded_rectangle(float x1, float y1, float x2, float y2, float rx, float ry);

	/** Draws a quadrilateral given its four vertices. This call uses the PaintBrush of the Window to draw, if needed.
	*	The quadrilateral is drawn as follows: a line connects first and second point, then a line connects second point and the third, then the third is connected to the fourth and finally a line connects fourth and first points.
	*	For example this code:
	*	@include quadrilateral_3.cpp
	*	Would generate this output:
	*	@image html quadrilateral.png
	*	@image latex quadrilateral.eps
	*	@param x1 X coordinate of the first point.
	*	@param y1 Y coordinate of the first point.
	*	@param x2 X coordinate of the second point.
	*	@param y2 Y coordinate of the second point.
	*	@param x3 X coordinate of the third point.
	*	@param y3 Y coordinate of the third point.
	*	@param x4 X coordinate of the fourth point.
	*	@param y4 Y coordinate of the fourth point.
	*/
	void quadrilateral(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

	/** Draws a filled quadrilateral given its four vertices. This call uses the PaintBrush of the Window to draw, if needed.
	*	The quadrilateral is drawn as follows: a line connects first and second point, then a line connects second point and the third, then the third is connected to the fourth and finally a line connects fourth and first points.
	*	For example this code:
	*	@include filled_quadrilateral_3.cpp
	*	Would generate this output:
	*	@image html filled_quadrilateral.png
	*	@image latex filled_quadrilateral.eps
	*	@param x1 X coordinate of the first point.
	*	@param y1 Y coordinate of the first point.
	*	@param x2 X coordinate of the second point.
	*	@param y2 Y coordinate of the second point.
	*	@param x3 X coordinate of the third point.
	*	@param y3 Y coordinate of the third point.
	*	@param x4 X coordinate of the fourth point.
	*	@param y4 Y coordinate of the fourth point.
	*/
	void filled_quadrilateral(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

	/** Draws an ellipse given its center's coordinates and its radii. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include ellipse_3.cpp
	*	Would generate this output:
	*	@image html ellipse.png
	*	@image latex ellipse.eps
	*	@param cx X coordinate of the center of the ellipse.
	*	@param cy Y coordinate of the center of the ellipse.
	*	@param rx Horizontal radius of the ellipse.
	*	@param ry Vertical radius of the ellipse.
	*/
	void ellipse(float cx, float cy, float rx, float ry);
	
	/** Draws a filled ellipse given its center's coordinates and its radii. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include filled_ellipse_3.cpp
	*	Would generate this output:
	*	@image html filled_ellipse.png
	*	@image latex filled_ellipse.eps
	*	@param cx X coordinate of the center of the ellipse.
	*	@param cy Y coordinate of the center of the ellipse.
	*	@param rx Horizontal radius of the ellipse.
	*	@param ry Vertical radius of the ellipse.
	*/
	void filled_ellipse(float cx, float cy, float rx, float ry);
	
	/** Draws a circle given its center's coordinates and its radius. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include circle_3.cpp
	*	Would generate this output:
	*	@image html circle.png
	*	@image latex circle.eps
	*	@param cx X coordinate of the center of the circle.
	*	@param cy Y coordinate of the center of the circle.
	*	@param r Radius of the circle.
	*/
	void circle(float cx, float cy, float r);
	
	/** Draws a filled circle given its center's coordinates and its radius. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include filled_circle_3.cpp
	*	Would generate this output:
	*	@image html filled_circle.png
	*	@image latex filled_circle.eps
	*	@param cx X coordinate of the center of the circle.
	*	@param cy Y coordinate of the center of the circle.
	*	@param r Radius of the circle.
	*/
	void filled_circle(float cx, float cy, float r);
	
	/** Draws an arc given its center's coordinates, its radius and the angle it describes. The angle is represented as the start point of the angle <EM>start_theta</EM>, and the angle increase <EM>delta_theta</EM>. This angle can be expressed in radians or degrees depending on the Window configuration (degrees by default). This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include arc_3.cpp
	*	Would generate this output:
	*	@image html arc.png
	*	@image latex arc.eps
	*	@param cx X coordinate of the center of the arc.
	*	@param cy Y coordinate of the center of the arc.
	*	@param r Radius of the arc.
	*	@param start_theta Start point of the angle.
	*	@param delta_theta Angle increase.
	*/
	void arc(float cx, float cy, float r, float start_theta, float delta_theta);
	
	/** Draws an arc given its center's coordinates, its radius and the angle it describes. The angle is represented as the start point of the angle <EM>start_theta</EM>, and the angle increase <EM>delta_theta</EM>. This angle can be expressed in radians or degrees depending on the Window configuration (degrees by default). This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include elliptical_arc_3.cpp
	*	Would generate this output:
	*	@image html elliptical_arc.png
	*	@image latex elliptical_arc.eps
	*	@param cx X coordinate of the center of the arc.
	*	@param cy Y coordinate of the center of the arc.
	*	@param rx Horizontal radius of the arc.
	*	@param ry Vertical radius of the arc.
	*	@param start_theta Start point of the angle.
	*	@param delta_theta Angle increase.
	*/
	void elliptical_arc(float cx, float cy, float rx, float ry, float start_theta, float delta_theta);
	
	/** Draws a pie slice given its center's coordinates, its radius and the angle it describes. The angle is represented as the start point of the angle <EM>start_theta</EM>, and the angle increase <EM>delta_theta</EM>. This angle can be expressed in radians or degrees depending on the Window configuration (degrees by default). This call uses the PaintBrush of the Window to draw, if needed.
	*	You can think of it as a "closed arc", an arc which its outermost radii are drawn as well.
	*	For example this code:
	*	@include pieslice_3.cpp
	*	Would generate this output:
	*	@image html pie slice.png
	*	@image latex pie slice.eps
	*	@param cx X coordinate of the center of the pie slice.
	*	@param cy Y coordinate of the center of the pie slice.
	*	@param r Radius of the pie slice.
	*	@param start_theta Start point of the angle.
	*	@param delta_theta Angle increase.
	*/
	void pieslice(float cx, float cy, float r, float start_theta, float delta_theta);
	
	/** Draws a filled pie slice given its center's coordinates, its radius and the angle it describes. The angle is represented as the start point of the angle <EM>start_theta</EM>, and the angle increase <EM>delta_theta</EM>. This angle can be expressed in radians or degrees depending on the Window configuration (degrees by default). This call uses the PaintBrush of the Window to draw, if needed.
	*	You can think of it as a "filled arc".
	*	For example this code:
	*	@include filled_pieslice_3.cpp
	*	Would generate this output:
	*	@image html filled_pieslice.png
	*	@image latex filled_pieslice.eps
	*	@param cx X coordinate of the center of the pie slice.
	*	@param cy Y coordinate of the center of the pie slice.
	*	@param r Radius of the pie slice.
	*	@param start_theta Start point of the angle.
	*	@param delta_theta Angle increase.
	*/
	void filled_pieslice(float cx, float cy, float r, float start_theta, float delta_theta);
	
	/** Draws a Bézier spline given its 4 control points. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include spline_3.cpp
	*	Would generate this output:
	*	@image html spline.png
	*	@image latex spline.eps
	*	@param points An array of X and Y coordinates describing the points of the spline.
	*/
	void spline(float points[8]);
	
	/** Draws a ribbon given its segments' start and end points and the number of points. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include ribbon_3.cpp
	*	Would generate this output:
	*	@image html ribbon.png
	*	@image latex ribbon.eps
	*	@param points An array of X and Y coordinates describing the points of the ribbon.
	*	@param num_points The number of points (pairs of X and Y coordinates) that <EM>points</EM> contains.
	*	@pre <EM>num_points</EM> must be less or equal than the real <EM>points</EM> buffer length divided by 2.
	*/
	void ribbon(const float *points, int num_points);
	
	/** @addtogroup text_operations 
	*	@{
	*/
	
	/** Puts a text into the screen. By default, the text is aligned to the left. Depending on the alignment, the point passed will represent different positions of the text box. 
	*	When aligned left, the point passed will be the top left corner of the text box. When aligned right, it will be the top right corner, and when aligned to the center, the point will represent the exact center of the text box. This call uses the active Font of the Window to put the text.
	*	For example this code:
	*	@include text_5.cpp
	*	Would generate this output:
	*	@image html text.png
	*	@image latex text.eps
	*	@param x X coordinate where the text will be drawn
	*	@param y Y coordinate where the text will be drawn.
	*	@param text The text that will be written.
	*	@param flags This parameter can be used to specify the alignment of the text. See @ref text_align for more details. Its value is <EM>0</EM> by default.
	*/
	void text(float x, float y, std::string text, int flags = 0);
	
	/** @}*/
	
	/** Draws a polyline on the screen. Similar to <EM>ribbon</EM>, but this call allows you to configure more parameters. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include polyline_3.cpp
	*	Would generate this output:
	*	@image html polyline.png
	*	@image latex polyline.eps
	*	@param vertices An array of X and Y coordinates describing the vertices of the polyline.
	*	@param vertex_count The number of vertices (pairs of X and Y coordinates) that <EM>vertices</EM> contains.
	*	@param join_style The way the lines join together. See @ref line_join for more details. Its value is <EM>LINE_JOIN_NONE</EM> by default.
	*	@param cap_style The way the lines join together. See @ref line_cap for more details. Its value is <EM>LINE_CAP_NONE</EM> by default.
	*	@param miter_limit Size of the miter. See @ref line_join for more details. Its value is <EM>0</EM> by default.
	*	@pre <EM>vertex_count</EM> must be less or equal than the real <EM>vertices</EM> buffer length divided by 2.
	*/
	void polyline(const float* vertices, int vertex_count, int join_style = LINE_JOIN_NONE, int cap_style = LINE_CAP_NONE, float miter_limit = 0);
	
	/** Draws a polygon on the screen. Similar to <EM>polyline</EM>, but joining the first point with the last one. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include polygon_3.cpp
	*	Would generate this output:
	*	@image html polygon.png
	*	@image latex polygon.eps
	*	@param vertices An array of X and Y coordinates describing the vertices of the polygon.
	*	@param vertex_count The number of vertices (pairs of X and Y coordinates) that <EM>vertices</EM> contains.
	*	@param join_style The way the lines join together. See @ref line_join for more details. Its value is <EM>LINE_JOIN_NONE</EM> by default.
	*	@param miter_limit Size of the miter. See @ref line_join for more details. Its value is <EM>0</EM> by default.
	*	@pre <EM>vertex_count</EM> must be less or equal than the real <EM>vertices</EM> buffer length divided by 2.
	*/
	void polygon(const float *vertices, int vertex_count, int join_style = LINE_JOIN_NONE, float miter_limit = 0);
	
	/** Draws a filled polygon on the screen. Note that when drawing a filled polygon you cannot use the @ref line_join modifiers. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include filled_polygon_3.cpp
	*	Would generate this output:
	*	@image html filled_polygon.png
	*	@image latex polygon.eps
	*	@param vertices An array of X and Y coordinates describing the vertices of the polygon.
	*	@param vertex_count The number of vertices (pairs of X and Y coordinates) that <EM>vertices</EM> contains.
	*	@pre <EM>vertex_count</EM> must be less or equal than the real <EM>vertices</EM> buffer length divided by 2.
	*/
	void filled_polygon(const float *vertices, int vertex_count);
	
	/** Draws a filled polygon with holes inside it on the screen. The holes must not intersect with the polygon outline. Note that when drawing a filled polygon you cannot use the @ref line_join modifiers. This call uses the PaintBrush of the Window to draw, if needed.
	*	This call is a little special, and the parameters have to be configured in a specific way (see precondition). Here's an example of how you have to do it
	*	@include filled_polygon_with_holes_3.cpp
	*	There are 7 vertices: four for an outer trapezoid in anti - clockwise order, and three more for an inner triangle in clockwise order. The outer main polygon uses vertices 0 to 3 (inclusive) and the hole uses vertices 4 to 6 (inclusive).
	*	This code would generate this output:
	*	@image html filled_polygon_with_holes.png
	*	@image latex filled_polygon_with_holes.eps
	*	@param vertices An array of X and Y coordinates describing the vertices of the polygon and also the vertices of the holes.
	*	@param vertex_counts The number of vertices (pairs of X and Y coordinates) that <EM>vertices</EM> contains.
	*	@pre <EM>vertex_count</EM> must be a 0 terminated array, which the total sum of its elements must be less or equal than the real <EM>vertices</EM> buffer length divided by 2.
	*		To effectively draw this figure, points of the holes must be ordered in the reverse order of the filled polygon vertices.
	*/
	void filled_polygon_with_holes(const float *vertices, const int *vertex_counts);

	//methods that use struct Point2D (to represent X and Y coordinates and) and class settings to draw
	
	/** Draws a pixel at the p position. It can be slow, so if you want to draw some figures consider using another primitive. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include pixel_4.cpp
	*	Would generate this output:
	*	@image html pixel.png
	*	@image latex pixel.eps
	*	@param p The point where the pixel will be drawn.
	*/
	void pixel(Point2D p);
	
	/** Draws a line between two points. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include line_4.cpp
	*	Would generate this output:
	*	@image html line.png
	*	@image latex line.eps
	*	@param p1 coordinates of the first point.
	*	@param p2 coordinates of the second point.
	*/
	void line(Point2D p1, Point2D p2);

	/** Draws a triangle between three points. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include triangle_4.cpp
	*	Would generate this output:
	*	@image html triangle.png
	*	@image latex triangle.eps
	*	@param p1 coordinates of the first point.
	*	@param p2 coordinates of the second point.
	*	@param p3 coordinates of the third point.
	*/
	void triangle(Point2D p1, Point2D p2, Point2D p3);
	
	/** Draws a filled triangle given its three vertices coordinates. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include filled_triangle_4.cpp
	*	Would generate this output:
	*	@image html filled_triangle.png
	*	@image latex filled_triangle.eps
	*	@param p1 coordinates of the first point.
	*	@param p2 coordinates of the second point.
	*	@param p3 coordinates of the third point.
	*/
	void filled_triangle(Point2D p1, Point2D p2, Point2D p3);
	
	/** Draws a rectangle given its top left and bottom right corners' coordinates. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include rectangle_4.cpp
	*	Would generate this output:
	*	@image html rectangle.png
	*	@image latex rectangle.eps
	*	@param p1 coordinates of the top left corner.
	*	@param p2 coordinates of the bottom right corner.
	*/
	void rectangle(Point2D p1, Point2D p2);
	
	/** Draws a filled rectangle given its top left and bottom right corners' coordinates. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include filled_rectangle_4.cpp
	*	Would generate this output:
	*	@image html filled_rectangle.png
	*	@image latex filled_rectangle.eps
	*	@param p1 coordinates of the top left corner.
	*	@param p2 coordinates of the bottom right corner.
	*/
	void filled_rectangle(Point2D p1, Point2D p2);
	
	/** Draws a rounded rectangle given its top left and bottom right corners' coordinates and its rounding radii. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include rounded_rectangle_4.cpp
	*	Would generate this output:
	*	@image html rounded_rectangle.png
	*	@image latex rounded_rectangle.eps
	*	<strong>NOTE</strong>: When rounding the rectangle, an ellipse is used to draw the curves around the corners (see figure below). The <EM>rx</EM> and <EM>ry</EM> parameters are the radii of the ellipse.
	*	@image html border_radius.png
	*	@image latex border_radius.eps
	*	@param p1 coordinates of the top left corner.
	*	@param p2 coordinates of the bottom right corner.
	*	@param rx Horizontal radius of the rounding ellipse.
	*	@param ry Vertical radius of the rounding ellipse.
	*/
	void rounded_rectangle(Point2D p1, Point2D p2, float rx, float ry);

	/** Draws a quadrilateral given its four vertices. This call uses the PaintBrush of the Window to draw, if needed.
	*	The quadrilateral is drawn as follows: a line connects first and second point, then a line connects second point and the third, then the third is connected to the fourth and finally a line connects fourth and first points.
	*	For example this code:
	*	@include quadrilateral_42.cpp
	*	Would generate this output:
	*	@image html quadrilateral.png
	*	@image latex quadrilateral.eps
	*	@param p1 coordinates of the first point.
	*	@param p2 coordinates of the second point.
	*	@param p3 coordinates of the third point.
	*	@param p4 coordinates of the fourth point.
	*/
	void quadrilateral(Point2D p1, Point2D p2, Point2D p3, Point2D p4);

	/** Draws a filled quadrilateral given its four vertices. This call uses the PaintBrush of the Window to draw, if needed.
	*	The quadrilateral is drawn as follows: a line connects first and second point, then a line connects second point and the third, then the third is connected to the fourth and finally a line connects fourth and first points.
	*	For example this code:
	*	@include filled_quadrilateral_4.cpp
	*	Would generate this output:
	*	@image html filled_quadrilateral.png
	*	@image latex filled_quadrilateral.eps
	*	@param p1 coordinates of the first point.
	*	@param p2 coordinates of the second point.
	*	@param p3 coordinates of the third point.
	*	@param p4 coordinates of the fourth point.
	*/
	void filled_quadrilateral(Point2D p1, Point2D p2, Point2D p3, Point2D p4);

	/** Draws a rounded rectangle given its top left and bottom right corners' coordinates and its rounding radii. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include filled_rounded_rectangle_4.cpp
	*	Would generate this output:
	*	@image html rounded_rectangle.png
	*	@image latex rounded_rectangle.eps
	*	<strong>NOTE</strong>: When rounding the rectangle, an ellipse is used to draw the curves around the corners (see figure below). The <EM>rx</EM> and <EM>ry</EM> parameters are the radii of the ellipse.
	*	@image html border_radius.png
	*	@image latex border_radius.eps
	*	@param p1 coordinates of the top left corner.
	*	@param p2 coordinates of the bottom right corner.
	*	@param rx Horizontal radius of the rounding ellipse.
	*	@param ry Vertical radius of the rounding ellipse.
	*/
	void filled_rounded_rectangle(Point2D p1, Point2D p2, float rx, float ry);
	
	/** Draws an ellipse given its center's coordinates and its radii. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include ellipse_4.cpp
	*	Would generate this output:
	*	@image html ellipse.png
	*	@image latex ellipse.eps
	*	@param c coordinates of the center of the ellipse.
	*	@param rx Horizontal radius of the ellipse.
	*	@param ry Vertical radius of the ellipse.
	*/
	void ellipse(Point2D c, float rx, float ry);
	
	/** Draws a filled ellipse given its center's coordinates and its radii. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include filled_ellipse_4.cpp
	*	Would generate this output:
	*	@image html filled_ellipse.png
	*	@image latex filled_ellipse.eps
	*	@param c coordinates of the center of the ellipse.
	*	@param rx Horizontal radius of the ellipse.
	*	@param ry Vertical radius of the ellipse.
	*/
	void filled_ellipse(Point2D c, float rx, float ry);
	
	/** Draws a circle given its center's coordinates and its radius. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include circle_4.cpp
	*	Would generate this output:
	*	@image html circle.png
	*	@image latex circle.eps
	*	@param c coordinates of the center of the circle.
	*	@param r Radius of the circle.
	*/
	void circle(Point2D c, float r);
	
	/** Draws a filled circle given its center's coordinates and its radius. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include filled_circle_4.cpp
	*	Would generate this output:
	*	@image html filled_circle.png
	*	@image latex filled_circle.eps
	*	@param c coordinates of the center of the circle.
	*	@param r Radius of the circle.
	*/
	void filled_circle(Point2D c, float r);
	
	/** Draws an arc given its center's coordinates, its radius and the angle it describes. The angle is represented as the start point of the angle <EM>start_theta</EM>, and the angle increase <EM>delta_theta</EM>. This angle can be expressed in radians or degrees depending on the Window configuration (degrees by default). This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include arc_4.cpp
	*	Would generate this output:
	*	@image html arc.png
	*	@image latex arc.eps
	*	@param c coordinates of the center of the arc.
	*	@param r Radius of the arc.
	*	@param start_theta Start point of the angle.
	*	@param delta_theta Angle increase.
	*/
	void arc(Point2D c, float r, float start_theta, float delta_theta);
	
	/** Draws an arc given its center's coordinates, its radius and the angle it describes. The angle is represented as the start point of the angle <EM>start_theta</EM>, and the angle increase <EM>delta_theta</EM>. This angle can be expressed in radians or degrees depending on the Window configuration (degrees by default). This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include elliptical_arc_4.cpp
	*	Would generate this output:
	*	@image html elliptical_arc.png
	*	@image latex elliptical_arc.eps
	*	@param c coordinates of the center of the arc.
	*	@param rx Horizontal radius of the arc.
	*	@param ry Vertical radius of the arc.
	*	@param start_theta Start point of the angle.
	*	@param delta_theta Angle increase.
	*/
	void elliptical_arc(Point2D c, float rx, float ry, float start_theta, float delta_theta);
	
	/** Draws a pie slice given its center's coordinates, its radius and the angle it describes. The angle is represented as the start point of the angle <EM>start_theta</EM>, and the angle increase <EM>delta_theta</EM>. This angle can be expressed in radians or degrees depending on the Window configuration (degrees by default). This call uses the PaintBrush of the Window to draw, if needed.
	*	You can think of it as a "closed arc", an arc which its outermost radii are drawn as well.
	*	For example this code:
	*	@include pieslice_4.cpp
	*	Would generate this output:
	*	@image html pie slice.png
	*	@image latex pie slice.eps
	*	@param c coordinates of the center of the pie slice.
	*	@param r Radius of the pie slice.
	*	@param start_theta Start point of the angle.
	*	@param delta_theta Angle increase.
	*/
	void pieslice(Point2D c, float r, float start_theta, float delta_theta);
	
	/** Draws a filled pie slice given its center's coordinates, its radius and the angle it describes. The angle is represented as the start point of the angle <EM>start_theta</EM>, and the angle increase <EM>delta_theta</EM>. This angle can be expressed in radians or degrees depending on the Window configuration (degrees by default). This call uses the PaintBrush of the Window to draw, if needed.
	*	You can think of it as a "filled arc".
	*	For example this code:
	*	@include filled_pieslice_4.cpp
	*	Would generate this output:
	*	@image html filled_pieslice.png
	*	@image latex filled_pieslice.eps
	*	@param c coordinates of the center of the pie slice.
	*	@param r Radius of the pie slice
	*	@param start_theta Start point of the angle
	*	@param delta_theta Angle increase
	*/
	void filled_pieslice(Point2D c, float r, float start_theta, float delta_theta);
	
	/** Draws a Bézier spline given its 4 control points. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include spline_4.cpp
	*	Would generate this output:
	*	@image html spline.png
	*	@image latex spline.eps
	*	@param points An array of coordinates describing the points of the spline.
	*/
	void spline(Point2D points[4]);
	
	/** Draws a ribbon given its segments' start and end points and the number of points. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include ribbon_4.cpp
	*	Would generate this output:
	*	@image html ribbon.png
	*	@image latex ribbon.eps
	*	@param points An array of coordinates describing the points of the ribbon.
	*	@param num_points The number of points that <EM>points</EM> contains.
	*	@pre <EM>num_points</EM> must be less or equal than the real <EM>points</EM> buffer length.
	*/
	void ribbon(const Point2D *points, int num_points);
	
	/** @addtogroup text_operations 
	*	@{
	*/
	
	/** Puts a text into the screen. By default, the text is aligned to the left. Depending on the alignment, the point passed will represent different positions of the text box. 
	*	When aligned left, the point passed will be the top left corner of the text box. When aligned right, it will be the top right corner, and when aligned to the center, the point will represent the exact center of the text box. This call uses the active Font of the Window to put the text.
	*	For example this code:
	*	@include text_6.cpp
	*	Would generate this output:
	*	@image html text.png
	*	@image latex text.eps
	*	@param p coordinates where the text will be drawn.
	*	@param text The text that will be written.
	*	@param flags This parameter can be used to specify the alignment of the text. See @ref text_align for more details. Its value is <EM>0</EM> by default.
	*/
	void text(Point2D p, std::string text, int flags = 0);
	
	/** @}*/
	
	/** Draws a polyline on the screen. Similar to <EM>ribbon</EM>, but this call allows you to configure more parameters. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include polyline_4.cpp
	*	Would generate this output:
	*	@image html polyline.png
	*	@image latex polyline.eps
	*	@param vertices An array of coordinates describing the vertices of the polyline.
	*	@param vertex_count The number of vertices that <EM>vertices</EM> contains.
	*	@param join_style The way the lines join together. See @ref line_join for more details. Its value is <EM>LINE_JOIN_NONE</EM> by default.
	*	@param cap_style The way the lines join together. See @ref line_cap for more details. Its value is <EM>LINE_CAP_NONE</EM> by default.
	*	@param miter_limit Size of the miter. See @ref line_join for more details. Its value is <EM>0</EM> by default.
	*	@pre <EM>vertex_count</EM> must be less or equal than the real <EM>vertices</EM> buffer length.
	*/
	void polyline(const Point2D *vertices, int vertex_count, int join_style = LINE_JOIN_NONE, int cap_style = LINE_CAP_NONE, float miter_limit = 0);
	
	/** Draws a polygon on the screen. Similar to <EM>polyline</EM>, but joining the first point with the last one. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include polygon_4.cpp
	*	Would generate this output:
	*	@image html polygon.png
	*	@image latex polygon.eps
	*	@param vertices An array of coordinates describing the vertices of the polygon.
	*	@param vertex_count The number of vertices that <EM>vertices</EM> contains.
	*	@param join_style The way the lines join together. See @ref line_join for more details. Its value is <EM>LINE_JOIN_NONE</EM> by default.
	*	@param miter_limit Size of the miter. See @ref line_join for more details. Its value is <EM>0</EM> by default.
	*	@pre <EM>vertex_count</EM> must be less or equal than the real <EM>vertices</EM> buffer length.
	*/
	void polygon(const Point2D *vertices, int vertex_count, int join_style = LINE_JOIN_NONE, float miter_limit = 0);
	
	/** Draws a filled polygon on the screen. Note that when drawing a filled polygon you cannot use the @ref line_join modifiers. This call uses the PaintBrush of the Window to draw, if needed.
	*	For example this code:
	*	@include filled_polygon_4.cpp
	*	Would generate this output:
	*	@image html filled_polygon.png
	*	@image latex polygon.eps
	*	@param vertices An array of coordinates describing the vertices of the polygon.
	*	@param vertex_count The number of vertices that <EM>vertices</EM> contains.
	*	@pre <EM>vertex_count</EM> must be less or equal than the real <EM>vertices</EM> buffer length.
	*/
	void filled_polygon(const Point2D *vertices, int vertex_count);
	
	/** Draws a filled polygon with holes inside it on the screen. The holes must not intersect with the polygon outline. Note that when drawing a filled polygon you cannot use the @ref line_join modifiers. This call uses the PaintBrush of the Window to draw, if needed.
	*	This call is a little special, and the parameters have to be configured in a specific way (see precondition). Here's an example of how you have to do it
	*	@include filled_polygon_with_holes_4.cpp
	*	There are 7 vertices: four for an outer trapezoid in anti - clockwise order, and three more for an inner triangle in clockwise order. The outer main polygon uses vertices 0 to 3 (inclusive) and the hole uses vertices 4 to 6 (inclusive).
	*	This code would generate this output:
	*	@image html filled_polygon_with_holes.png
	*	@image latex filled_polygon_with_holes.eps
	*	@param vertices An array of coordinates describing the vertices of the polygon and also the vertices of the holes.
	*	@param vertex_counts The number of vertices (pairs of X and Y coordinates) that <EM>vertices</EM> contains.
	*	@pre <EM>vertex_count</EM> must be a 0 terminated array, which the total sum of its elements must be less or equal than the real <EM>vertices</EM> buffer length.
	*		To effectively draw this figure, points of the holes must be ordered in the reverse order of the filled polygon vertices.
	*/
	void filled_polygon_with_holes(const Point2D *vertices, const int *vertex_counts);

	/** @}*/
	
	/** @defgroup text_operations Text primitives
	*/	
	
	/** Given a Drawable object, draws it on the Window.
	*	@param draw_target Drawable object.
	*/
	void draw(Drawable * draw_target);
	
	/** Given an array of Drawable objects, draws them on the Window.
	*	@param draw_target Drawable object array.
	*	@param size Size of the array.
	*/
	void draw(Drawable** draw_target, size_t size);
	
	
	template<class InputIterator> //Templates are awesome!
	
	/** Given two iterators over a structure of Drawable objects, draws the elements in the interval [first, last).
	*	@param first Iteration starting point.
	*	@param last Iteration end point (not included).
	*/
	void draw(InputIterator first, InputIterator last)
	{
		bool autoUpdate = _autoUpdate;
		disableAutoUpdate();

		for (InputIterator it = first; it != last; it++) {
			(*it)->draw(*this);
		}

		_autoUpdate = autoUpdate;
		this->autoUpdate();
	}

	/** Causes the Window (and the thread using it) to sleep for the amount of time specified by the user.
	*	@param time Floating point time in seconds.
	*/
	void rest(float time);
	
	/** Updates the screen, drawing all buffered draw calls if any.
	*/
	void update();
	
	/** Clears to background color and deletes all logged draw calls if any.
	*/
	void clear();
	
	/** Enables Auto Update functionality. When Auto Update is enabled, the screen refreshes itself every time a draw call is made.
	*/
	void enableAutoUpdate();
	
	/** Disables Auto Update functionality. When Auto Update is disabled, the only way to refresh the screen is calling <EM>update()</EM> function.
	*/
	void disableAutoUpdate();
	
	/** Enables Logging functionality. When Logging is enabled, every draw call made on this Window is logged and can be redrawn when needed (for example when the background color is changed).
	*/
	void enableLogging();
	
	/** Disables Logging functionality. When Logging is disabled, no draw call made on this Window is logged, so if you clear the screen all your drawings will be erased.
	*/
	void disableLogging();
	
	/** Disables showing the mouse cursor when it's over the Window.
	*/
	void hideCursor();
	
	/** Enables showing the mouse cursor when it's over the Window.
	*/
	void showCursor();
	
	/** Changes the units of Window angles to Radians.
	*/
	void useRadians();
	
	/** Changes the units of Window angles to Degrees.
	*/
	void useDegrees();

	/** Changes the background color of the Window.
	*	@param r Red value of the new background color.
	*	@param g Green value of the new background color.
	*	@param b Blue value of the new background color.
	*	@param a Alpha value of the new background color.
	*/
	void changeBackgroundColor(int r, int g, int b, int a);
	
	/** Changes the background color of the Window.
	*	@param c New background color.
	*/
	void changeBackgroundColor(RGBColor c);
	
	/** Changes the drawing color of the Window.
	*	@param r Red value of the new drawing color.
	*	@param g Green value of the new drawing color.
	*	@param b Blue value of the new drawing color.
	*	@param a Alpha value of the new drawing color.
	*/
	void changeDrawingColor(int r, int g, int b, int a);
	
	/** Changes the drawing color of the Window.
	*	@param c new drawing color.
	*/
	void changeDrawingColor(RGBColor c);
	
	/** Changes the thickness of the PaintBrush of the Window.
	*	@param thickness new line thickness.
	*/
	void changeDrawingThickness(float thickness);

	//Font routines
	
	/** Adds a new Font to the Font list of the Window.
	*	@param font_name the name that will be used to identify this Font in the list.
	*	@param font_path the path where the Font source is.
	*	@param size Font size. Its value is <EM>DEFAULT_FONT_SIZE = 12</EM> by default.
	*	@param color Color of the Font. Its value is <EM>DEFAULT_FONT_COLOR = BLACK</EM> by default.
	*	@param flags Font flags. Its value is <EM>DEFAULT_FONT_FLAGS = 0</EM> by default.
	*	@return A boolean value, <EM>true</EM> if the Font has been successfully added, false otherwise.
	*/
	bool addFont(std::string font_name, std::string font_path, RGBColor color = DEFAULT_FONT_COLOR, int size = DEFAULT_FONT_SIZE, int flags = DEFAULT_FONT_FLAGS);
	
	/** Adds an existing Font to the Font list of the Window.
	*	@param font_name Name that will be used to identify this Font in the list.
	*	@param f The Font to be added.
	*	@return A boolean value, <EM>true</EM> if the Font has been successfully added, false otherwise.
	*/
	bool addFont(std::string font_name, Font & f);
	
	/** Removes the font from the Window's Font list. If the font cannot be found in the list, then it will throw an exception.
	*	@param font_name Name that will be used to identify this Font in the list.
	*	@return A boolean value, <EM>true</EM> if the Font has been successfully removed, false otherwise.
	*/
	bool deleteFont(std::string font_name);
	
	/** @return A copy of the active Font of the Window.
	*/
	Font getActiveFont() const;
	
	/** @return A copy of the default Font of the Window.
	*/
	Font getDefaultFont() const;
	
	/** Sets a new active Font given its name in the list. The font must be in the Font list in order to be set as active.
	*	@param font_name Name of the font.
	*	@return A boolean value, <EM>true</EM> if the Font has been successfully found and set as the active one, false otherwise.
	*/
	bool setActiveFont(std::string font_name);
	
	/** @return The number of fonts that the Font list contains.
	*/
	size_t nFonts() const;

	//Image routines
	
	/** @defgroup window_images Image methods
	*	A collection of methods that allows you to load and store bitmap drawings.
	*	@{
	*/
	
	/** Loads and returns an image from a file.
	*	@param file_path Path of the image.
	*	@return An Image, a container for the loaded bitmap.
	*/
	Image loadImage(std::string file_path);
	
	/** Saves the actual Window screen to a file (like a screenshot).
	*	@param save_path Full path (absolute or relative) without the file extension. Its value is <EM>"image"</EM> by default.
	*	@param extension Extension of the file. Its value is <EM>"png"</EM> by default.
	*	@return A boolean value, <EM>true</EM> if the image has been successfully saved, false otherwise.
	*/
	bool saveToFile(std::string save_path = "image", std::string extension = "png");
	
	/** Draws an Image to the screen. An image is drawn from its bottom left corner on the coordinates specified by the user.
	*	@param image Image to be drawn.
	*	@param x X coordinate of the point where bottom left corner will be drawn.
	*	@param y Y coordinate of the point where bottom left corner will be drawn.
	*	@param flags Flags for the bitmap drawing. Its value is <EM>0</EM> by default.
	*	@return A boolean value, <EM>true</EM> if the image has been successfully drawn, false otherwise.
	*/
	bool image(Image image, float x, float y, int flags = 0);
	
	/** Draws an Image to the screen. An image is drawn from its bottom left corner on the coordinates specified by the user.
	*	@param image Image to be drawn.
	*	@param p The point where bottom left corner will be drawn.
	*	@param flags Flags for the bitmap drawing. Its value is <EM>0</EM> by default.
	*	@return A boolean value, <EM>true</EM> if the image has been successfully drawn, false otherwise.
	*/
	bool image(Image image, Point2D p, int flags = 0);
	
	/** Draws an Image from a file to the screen. An image is drawn from its bottom left corner on the coordinates specified by the user.
	*	@param file_path Path of the image to be drawn.
	*	@param x X coordinate of the point where bottom left corner will be drawn.
	*	@param y Y coordinate of the point where bottom left corner will be drawn.
	*	@param flags Flags for the bitmap drawing. Its value is <EM>0</EM> by default.
	*	@return A boolean value, <EM>true</EM> if the image has been successfully loaded and drawn, false otherwise.
	*/
	bool image(std::string file_path, float x, float y, int flags = 0);
	
	/** Draws an Image from a file to the screen. An image is drawn from its bottom left corner on the coordinates specified by the user.
	*	@param file_path Path of the image to be drawn.
	*	@param p The point where bottom left corner will be drawn.
	*	@param flags Flags for the bitmap drawing. Its value is <EM>0</EM> by default.
	*	@return A boolean value, <EM>true</EM> if the image has been successfully loaded and drawn, false otherwise.
	*/
	bool image(std::string file_path, Point2D p, int flags = 0);
	
	/** Draws a rotated Image to the screen. An image is drawn from its bottom left corner on the coordinates specified by the user, and rotated relative to itself (not the Window).
	*	@param image Image to be drawn.
	*	@param cx X coordinate of the rotation point (relative to the image).
	*	@param cy Y coordinate of the rotation point (relative to the image).
	*	@param dx X coordinate of the point where bottom left corner will be drawn.
	*	@param dy Y coordinate of the point where bottom left corner will be drawn.
	*	@param angle Rotation angle.
	*	@param flags Flags for the bitmap drawing. Its value is <EM>0</EM> by default.
	*	@return A boolean value, <EM>true</EM> if the image has been successfully drawn, false otherwise.
	*/
	bool rotated_image(Image image, float cx, float cy, float dx, float dy, float angle, int flags = 0);
	
	/** Draws an Image to the screen. An image is drawn from its bottom left corner on the coordinates specified by the user.
	*	@param image Image to be drawn.
	*	@param c The rotation point (relative to the image).
	*	@param d The point where bottom left corner will be drawn.
	*	@param angle Rotation angle.
	*	@param flags Flags for the bitmap drawing. Its value is <EM>0</EM> by default.
	*	@return A boolean value, <EM>true</EM> if the image has been successfully drawn, false otherwise.
	*/
	bool rotated_image(Image image, Point2D c, Point2D d, float angle, int flags = 0);
	
	/** Draws a rotated Image to the screen. An image is drawn from its bottom left corner on the coordinates specified by the user, and rotated relative to itself (not the Window).
	*	@param file_path Path of the image to be drawn.
	*	@param cx X coordinate of the rotation point (relative to the image).
	*	@param cy Y coordinate of the rotation point (relative to the image).
	*	@param dx X coordinate of the point where bottom left corner will be drawn.
	*	@param dy Y coordinate of the point where bottom left corner will be drawn.
	*	@param angle Rotation angle.
	*	@param flags Flags for the bitmap drawing. Its value is <EM>0</EM> by default.
	*	@return A boolean value, <EM>true</EM> if the image has been successfully loaded and drawn, false otherwise.
	*/
	bool rotated_image(std::string file_path, float cx, float cy, float dx, float dy, float angle, int flags = 0);
	
	/** Draws an Image to the screen. An image is drawn from its bottom left corner on the coordinates specified by the user.
	*	@param file_path Path of the image to be drawn.
	*	@param c The rotation point (relative to the image).
	*	@param d The point where bottom left corner will be drawn.
	*	@param angle Rotation angle.
	*	@param flags Flags for the bitmap drawing. Its value is <EM>0</EM> by default.
	*	@return A boolean value, <EM>true</EM> if the image has been successfully loaded and drawn, false otherwise.
	*/
	bool rotated_image(std::string file_path, Point2D c, Point2D d, float angle, int flags = 0);
	
	/** @}*/
	
	//Turtle interaction
	
	/** @defgroup window_turtles Turtle methods
	*	Here you have all the functions used to interact with your collection of Turtles. 
	*	@{
	*/
	
	/** Adds a Turtle to the Window. With this function, the name of the turtle is the only parameter that can be chosen. The pen (PaintBrush) will be the same as the Window one, the start point will be <EM>TURTLE_HOME</EM> and the Font will be the active Font of the Window.
	*	@param turtle_name Name of the Turtle.
	*	@return A boolean value, <EM>true</EM> if the Turtle has been successfully added, false otherwise.
	*/
	bool addTurtle(std::string turtle_name);
	
	/** Adds a Turtle to the Window. With this function, the name of the turtle and its pen are the only parameter that can be chosen. The start point will be <EM>TURTLE_HOME</EM> and the Font will be the active Font of the Window.
	*	@param turtle_name Name of the Turtle.
	*	@param pen PaintBrush that the Turtle will use to draw its lines.
	*	@return A boolean value, <EM>true</EM> if the Turtle has been successfully added, false otherwise.
	*/
	bool addTurtle(std::string turtle_name, PaintBrush pen);
	
	/** Adds a Turtle to the Window. With this function, the parameters that can be chosen are the name of the turtle, its pen and the starting point of the Turtle. The Font will be the active Font of the Window.
	*	@param turtle_name Name of the Turtle.
	*	@param pen PaintBrush that the Turtle will use to draw its lines.
	*	@param start_point Point where the turtle will be spawned.
	*	@return A boolean value, <EM>true</EM> if the Turtle has been successfully added, false otherwise.
	*/
	bool addTurtle(std::string turtle_name, PaintBrush pen, Point2D start_point);
	
	/** Adds a Turtle to the Window. With this function you can choose any of the Turtle parameters.
	*	@param turtle_name Name of the Turtle.
	*	@param pen PaintBrush that the Turtle will use to draw its lines.
	*	@param start_point Point where the turtle will be spawned.
	*	@param font Font that the Turtle will use to draw text.
	*	@return A boolean value, <EM>true</EM> if the Turtle has been successfully added, false otherwise.
	*/
	bool addTurtle(std::string turtle_name, PaintBrush pen, Point2D start_point, Font & font);
	
	/** Releases (soft way to say removes) the Turtle from the list.
	*	@param turtle_name Name of the turtle. If the name doesn't exist in the list, this method will throw an Exception.
	*/
	bool releaseTurtle(std::string turtle_name);
	
	/** @return The name of the active Turtle.
	*/
	std::string activeTurtle() const;
	
	/** Given the name of a Turtle in the list, sets it as the active Turtle. If the name doesn't exist, the active Turtle will remain the same and the method will throw an Exception.
	*/
	bool setActiveTurtle(std::string turtle_name);
	
	/** @return The number of Turtles in the Window's list.
	*/
	size_t nTurtles() const;

	//Active turtle interaction
	
	/** @return The active Turtle's name.
	*/
	std::string t_getName() const;
	
	/** @return The active Turtle's actual orientation.
	*/
	float t_heading() const;
	
	/** @return The active Turtle's actual position.
	*/
	Point2D t_getPos() const;
	
	/** Moves the active Turtle forward the distance specified by the user.
	*	@param dist Distance.
	*	@return The Turtle's new position.
	*/
	Point2D t_forward(float dist);
	
	/** Moves the active Turtle forward the distance specified by the user.
	*	@param dist Distance.
	*	@return The Turtle's new position.
	*/
	Point2D t_back(float dist);
	
	/** Rotates the active Turtle to the left over itself.
	*	@param angle Rotation angle.
	*	@return The new direction.
	*/
	float t_left(float angle);
	
	/** Rotates the active Turtle to the right over itself.
	*	@param angle Rotation angle.
	*	@return The new direction.
	*/
	float t_right(float angle);
	
	/** Changes the position of the active Turtle given the new position.
	*	@param x X coordinate of the new position.
	*	@param y Y coordinate of the new position.
	*	@return The new position.
	*/
	Point2D t_setPos(float x, float y);
	
	/** Changes the position of the active Turtle given the new position.
	*	@param p The new position.
	*	@return The new position.
	*/
	Point2D t_setPos(Point2D p);
	
	/** Changes the heading (orientation) of the active Turtle given the new heading.
	*	@param angle The new heading.
	*	@return The new heading.
	*/
	float t_setHeading(float angle);
	
	/** Changes the pen of the active Turtle given the new PaintBrush.
	*	@param pen The new PaintBrush.
	*	@return The new PaintBrush.
	*/
	PaintBrush t_setPen(PaintBrush pen);
	
	/** Changes the pen of the active Turtle given a color. The thickness will be taken form the Window's PaintBrush.
	*	@param color The new color.
	*	@return The new PaintBrush.
	*/
	RGBColor t_setPen(RGBColor color);
	
	/** Changes the pen of the active Turtle given the color and the thickness of that pen.
	*	@param color The new color.
	*	@param thickness The new thickness.
	*	@return The new PaintBrush.
	*/
	RGBColor t_setPen(RGBColor color, float thickness);
	
	/** Sets active Turtle's position to <EM>TURTLE_HOME</EM>.
	*	@return The Turtle's new position.
	*/
	Point2D t_home();
	
	/** Sets the active Turtle's visibility to "visible". The cursor of the Turtle will be shown, and updated automatically every time <EM>update()</EM> function is called.
	*/
	void t_show();
	
	/** Sets the active Turtle's visibility to "not visible". The cursor of the Turtle will be hidden.
	*/
	void t_hide();
	
	/** Lifts up the active Turtle's pen, so she will not draw a line every time she moves.
	*/
	void t_penUp();
	
	/** Drops down the active Turtle's pen, so she will draw a line every time she moves.
	*/
	void t_penDown();
	
	/** Switches the pen state of the active Turtle, so if it's lifted up it drops down the pen and vice versa.
	*/
	void t_swapPen();
	
	/** @addtogroup text_operations 
	*	@{
	*/
	
	/** Puts a text on the position of the active Turtle using the Font of the Turtle.
	*	@param text Text to be drawn.
	*	@param flags Flags for the text.
	*/
	void t_label(std::string text, int flags);
	
	/** Puts a text on the position of the active Turtle.
	*	@param f Font used to draw the text.
	*	@param text Text to be drawn.
	*	@param flags Flags for the text.
	*/
	void t_label(Font f, std::string text, int flags);
	
	/** @}*/
	
	/** Puts an image aligning the bottom left corner of it with the position of the active Turtle.
	*	@param i Image to be drawn.
	*	@param flags Flags for the image.
	*/
	void t_image(Image i, int flags = 0);
	
	/** Loads and puts an image aligning the bottom left corner of it with the position of the active Turtle.
	*	@param image_path Path of the file that contains the image.
	*	@param flags Flags for the image.
	*/
	void t_image(std::string image_path, int flags = 0);
	
	/** Changes de motion type of the active Turtle. Actually this method does nothing.
	*	@param turtle_motion Type of new turtle motion.
	*/
	void t_changeMotion(int turtle_motion);
	
	/** Changes the font of the active Turtle
	*	@param f New Font.
	*/
	void t_setFont(Font f);

	//General turtle interaction
	
	/** Returns the name of the selected Turtle. Using this method means that you don't know what you're doing.
	*	@param turtle_name Name of the selected Turtle.
	*	@return Selected Turtle's name.
	*/
	std::string t_getName(std::string turtle_name) const; //This method is useless
	
	/** 
	*	@param turtle_name Name of the selected Turtle.
	*	@return Selected Turtle's actual orientation.
	*/
	float t_heading(std::string turtle_name) const;
	
	/** 
	*	@param turtle_name Name of the selected Turtle.
	*	@return Selected Turtle's actual position.
	*/
	Point2D t_getPos(std::string turtle_name) const;
	
	/** Moves the selected Turtle forward the distance specified by the user.
	*	@param turtle_name Name of the selected Turtle.
	*	@param dist Distance.
	*	@return The Turtle's new position.
	*/
	Point2D t_forward(std::string turtle_name, float dist);
	
	/** Moves the selected Turtle forward the distance specified by the user.
	*	@param turtle_name Name of the selected Turtle.
	*	@param dist Distance.
	*	@return The Turtle's new position.
	*/
	Point2D t_back(std::string turtle_name, float dist);
	
	/** Rotates the selected Turtle to the left over itself.
	*	@param turtle_name Name of the selected Turtle.
	*	@param angle Rotation angle.
	*	@return The new direction.
	*/
	float t_left(std::string turtle_name, float angle);
	
	/** Rotates the selected Turtle to the right over itself.
	*	@param turtle_name Name of the selected Turtle.
	*	@param angle Rotation angle.
	*	@return The new direction.
	*/
	float t_right(std::string turtle_name, float angle);
	
	/** Changes the position of the selected Turtle given the new position.
	*	@param turtle_name Name of the selected Turtle.
	*	@param x X coordinate of the new position.
	*	@param y Y coordinate of the new position.
	*	@return The new position.
	*/
	Point2D t_setPos(std::string turtle_name, float x, float y);
	
	/** Changes the position of the selected Turtle given the new position.
	*	@param turtle_name Name of the selected Turtle.
	*	@param p The new position.
	*	@return The new position.
	*/
	Point2D t_setPos(std::string turtle_name, Point2D p);
	
	/** Changes the heading (orientation) of the selected Turtle given the new heading.
	*	@param turtle_name Name of the selected Turtle.
	*	@param angle The new heading.
	*	@return The new heading.
	*/
	float t_setHeading(std::string turtle_name, float angle);
	
	/** Changes the pen of the selected Turtle given the new PaintBrush.
	*	@param turtle_name Name of the selected Turtle.
	*	@param pen The new PaintBrush.
	*	@return The new PaintBrush.
	*/
	PaintBrush t_setPen(std::string turtle_name, PaintBrush pen);
	
	/** Changes the pen of the selected Turtle given a color. The thickness will be taken form the Window's PaintBrush.
	*	@param turtle_name Name of the selected Turtle.
	*	@param color The new color.
	*	@return The new PaintBrush.
	*/
	RGBColor t_setPen(std::string turtle_name, RGBColor color);
	
	/** Changes the pen of the selected Turtle given the color and the thickness of that pen.
	*	@param turtle_name Name of the selected Turtle.
	*	@param color The new color.
	*	@param thickness The new thickness.
	*	@return The new PaintBrush.
	*/
	RGBColor t_setPen(std::string turtle_name, RGBColor color, float thickness);
	
	/** Sets active Turtle's position to <EM>TURTLE_HOME</EM>.
	*	@param turtle_name Name of the selected Turtle.
	*	@return The Turtle's new position.
	*/
	Point2D t_home(std::string turtle_name);
	
	/** Sets the selected Turtle's visibility to "visible". The cursor of the Turtle will be shown, and updated automatically every time <EM>update()</EM> function is called.
	*	@param turtle_name Name of the selected Turtle.
	*/
	void t_show(std::string turtle_name);
	
	/** Sets the selected Turtle's visibility to "not visible". The cursor of the Turtle will be hidden.
	*	@param turtle_name Name of the selected Turtle.
	*/
	void t_hide(std::string turtle_name);
	
	/** Lifts up the selected Turtle's pen, so she will not draw a line every time she moves.
	*	@param turtle_name Name of the selected Turtle.
	*/
	void t_penUp(std::string turtle_name);
	
	/** Drops down the selected Turtle's pen, so she will draw a line every time she moves.
	*	@param turtle_name Name of the selected Turtle.
	*/
	void t_penDown(std::string turtle_name);
	
	/** Switches the pen state of the selected Turtle, so if it's lifted up it drops down the pen and vice versa.
	*	@param turtle_name Name of the selected Turtle.
	*/
	void t_swapPen(std::string turtle_name);
	
	/** @addtogroup text_operations 
	*	@{
	*/
	
	/** Puts a text on the position of the selected Turtle using the Font of the Turtle.
	*	@param turtle_name Name of the selected Turtle.
	*	@param text Text to be drawn.
	*	@param flags Flags for the text.
	*/
	void t_label(std::string turtle_name, std::string text, int flags);
	
	/** Puts a text on the position of the selected Turtle.
	*	@param turtle_name Name of the selected Turtle.
	*	@param f Font used to draw the text.
	*	@param text Text to be drawn.
	*	@param flags Flags for the text.
	*/
	void t_label(std::string turtle_name, Font f, std::string text, int flags);
	
	/** @}*/
	
	/** Puts an image aligning the bottom left corner of it with the position of the selected Turtle.
	*	@param turtle_name Name of the selected Turtle.
	*	@param i Image to be drawn.
	*	@param flags Flags for the image.
	*/
	void t_image(std::string turtle_name, Image i, int flags);
	
	/** Loads and puts an image aligning the bottom left corner of it with the position of the selected Turtle.
	*	@param turtle_name Name of the selected Turtle.
	*	@param image_path Path of the file that contains the image.
	*	@param flags Flags for the image.
	*/
	void t_image(std::string turtle_name, std::string image_path, int flags);
	
	/** Changes de motion type of the selected Turtle. Actually this method does nothing.
	*	@param turtle_name Name of the selected Turtle.
	*	@param turtle_motion Type of new turtle motion.
	*/
	void t_changeMotion(std::string turtle_name, int turtle_motion);
	
	/** Changes the font of the selected Turtle
	*	@param turtle_name Name of the selected Turtle.
	*	@param f New Font.
	*/
	void t_setFont(std::string turtle_name, Font f);

	/** @}*/
	
	//Event handling 
	
	/** Waits for the next WindowEvent, without filters. Be careful, this method waits forever. If no event is triggered, the program will go on forever, without exiting this method. It's more recommendable to use @ref waitWindowEventTimed(float) to not to wait forever.
	*	@return The first WindowEvent in the EventQueue of the Window.
	*/
	WindowEvent waitWindowEvent();
	
	/** Waits for the next WindowEvent with the type specified by the user. Be careful, this method waits forever. If no event is triggered, the program will go on forever, without exiting this method. It's more recommendable to use @ref waitWindowEventTimed(WindowEventType, float) to not to wait forever. The events with different type are skipped and removed from the queue.
	*	@param ev_type Type of the target event.
	*	@return The first WindowEvent in the EventQueue of the Window with the same type as @p ev_type.
	*/
	WindowEvent waitWindowEvent(WindowEventType ev_type);
	
	/** Waits for the next WindowEvent, without filters, until the first WindowEvent arrives or the timeout expires. 
	*	@param seconds Max seconds to wait for an event.
	*	@return The first WindowEvent in the EventQueue of the Window if any, or a WindowTimerEvent if the timeout expires.
	*/
	WindowEvent waitWindowEventTimed(float seconds);
	
	/** Waits for the next WindowEvent with the type specified by the user until the first WindowEvent arrives or the timeout expires. The events with different type are skipped and removed from the queue.
	*	@param ev_type Type of the target event.
	*	@param seconds Max seconds to wait for an event.
	*	@return The first WindowEvent in the EventQueue of the Window with the same type as @p ev_type.
	*/
	WindowEvent waitWindowEventTimed(WindowEventType ev_type, float seconds);
	
	/** Waits for the next WindowEvent with the WindowEventType WINDOW_EVENT_MOUSE_BUTTON_UP or WINDOW_EVENT_MOUSE_BUTTON_DOWN on mouse left button, depending on @p on_release parameter. In other words, it waits until the left mouse button is pressed.
	*	@param on_release When true, the function waits for a "release" event, so it will wait for WINDOW_EVENT_MOUSE_BUTTON_UP, otherwise will wait for WINDOW_EVENT_MOUSE_BUTTON_DOWN. By default its value is @a false.
	*	@return The point where the mouse was clicked/released.
	*/
	Point2D waitMouseLeftClick(bool on_release = false);
	
	/** Waits for the next WindowEvent with the WindowEventType WINDOW_EVENT_MOUSE_BUTTON_UP or WINDOW_EVENT_MOUSE_BUTTON_DOWN on mouse right button, depending on @p on_release parameter. In other words, it waits until the left mouse button is pressed.
	*	@param on_release When true, the function waits for a "release" event, so it will wait for WINDOW_EVENT_MOUSE_BUTTON_UP, otherwise will wait for WINDOW_EVENT_MOUSE_BUTTON_DOWN. By default its value is @a false.
	*	@return The point where the mouse was clicked/released.
	*/
	Point2D waitMouseRightClick(bool on_release =  false);
	
	/** Waits for the next WindowEvent with the WindowEventType WINDOW_EVENT_MOUSE_BUTTON_UP or WINDOW_EVENT_MOUSE_BUTTON_DOWN on any mouse button, depending on @p on_release parameter. In other words, it waits until any mouse button is pressed.
	*	@param on_release When true, the function waits for a "release" event, so it will wait for WINDOW_EVENT_MOUSE_BUTTON_UP, otherwise will wait for WINDOW_EVENT_MOUSE_BUTTON_DOWN. By default its value is @a false.
	*	@return The point where the mouse was clicked/released.
	*/
	Point2D waitMouseAnyClick(bool on_release = false);
	
	/** Waits for the next WindowEvent with the WindowEventType WINDOW_EVENT_MOUSE_BUTTON_UP or WINDOW_EVENT_MOUSE_BUTTON_DOWN on the selected mouse button by the user, depending on @p on_release parameter. In other words, it waits until the selected mouse button is pressed.
	*	@param mouse_button Number of the target button to listen. It depends on every device, but usually the left button is 0 and right button is 1.
	*	@param on_release When true, the function waits for a "release" event, so it will wait for WINDOW_EVENT_MOUSE_BUTTON_UP, otherwise will wait for WINDOW_EVENT_MOUSE_BUTTON_DOWN. By default its value is @a false.
	*	@return The point where the mouse was clicked/released.
	*/
	Point2D waitMouseClick(unsigned int mouse_button = 0, bool on_release = false);
	
	/** Waits for the next WindowEvent with the WindowEventType WINDOW_EVENT_KEY_UP or WINDOW_EVENT_KEY_DOWN, depending on @p on_release parameter. In other words, it waits until any key is pressed.
	*	@param on_release When true, the function waits for a "release" event, so it will wait for WINDOW_EVENT_KEY_UP, otherwise will wait for WINDOW_EVENT_KEY_DOWN. By default its value is @a false.
	*	@return The keycode of the pressed key.
	*/
	int waitAnyKeypress(bool on_release = false);
	
	/** Waits for the next WindowEvent with the WindowEventType WINDOW_EVENT_KEY_UP or WINDOW_EVENT_KEY_DOWN, depending on @p on_release parameter and only waits for the selected key, ignoring the other keypresses. In other words, it waits until the selected key is pressed.
	*	@param key Keycode of the target key to listen. See Event for more details.
	*	@param on_release When true, the function waits for a "release" event, so it will wait for WINDOW_EVENT_KEY_UP, otherwise will wait for WINDOW_EVENT_KEY_DOWN. By default its value is @a false.
	*	@return The keycode of the pressed key.
	*/
	int waitKeypress(int key, bool on_release = false);
	
	/** Waits for the next WindowEvent with the WindowEventType WINDOW_EVENT_DISPLAY_CLOSE. In other words this method waits until the Window close button is pressed.
	*/
	void waitWindowCloseButton();

	/** @return A pointer to the ALLEGRO_DISPLAY of the Window. This is for more experienced users who want to unleash all the power of Allegro.
	*/
	ALLEGRO_DISPLAY* getDisplay(); //Release the beast
	
	/** @return The dimensions of the Window.
	*/
	WindowSpec getWindowSpec() const;

	//Turtle object interaction (SHOULDN'T BE USED BY USER CODE)
	
	/** @defgroup window_turtle_interaction Window-Turtle interaction
	*	This group of methods are intended to be used in a OOP object communication and not by users. However, it's safe to call them from anywhere of your program (but not recommended!)
	*	@{
	*/
	
	/** Notifies the Window that a Turtle has changed its position.
	*/
	void turtleMoved();
	
	/** Draws a Turtle line (similar to a line), interacting with the Window.
	*	@param p1 coordinates of the first point.
	*	@param p2 coordinates of the second point.
	*	@param color Color used to draw the line.
	*	@param thickness Thickness of the line.
	*	@param showing_cursor Indicates if the turtle using this function is visible or not.
	*/
	void turtleLine(Point2D p1, Point2D p2, RGBColor color, float thickness, bool showing_cursor);
	
	/** Draws an Image to the screen. An image is drawn from its bottom left corner on the coordinates specified by the user.
	*	@param image Image to be drawn.
	*	@param c The rotation point (relative to the image).
	*	@param d The point where bottom left corner will be drawn.
	*	@param angle Rotation angle.
	*	@param flags Flags for the bitmap drawing. Its value is <EM>0</EM> by default.
	*	@return A boolean value, <EM>true</EM> if the image has been successfully drawn, <em>false</em> otherwise.
	*/
	bool turtle_rotated_image(Image image, Point2D c, Point2D d, float angle, int flags = 0);
	
	/** Similar to Auto Update function but triggered by a Turtle.
	*/
	void cursorUpdate();

	/** @}*/
	
private:
	static const unsigned int POINTS_STRIDE = 2 * sizeof(float); /**< It's basically the size of two <EM>float</EM> variables. It's for Allegro purposes*/

	static int NUMBER_OF_DISPLAYS; /**< Number of displays instantiated. Same as the number of concurrent Window.*/

	//private methods
	
	/** Initializes the Window.
	*	@param window_title Title for the new Window.
	*	@param width Width of the Window.
	*	@param height Height of the Window.
	*	@param background_color Background color of the Window.
	*	@param drawing_color Drawing color of the Window.
	*	@param line_width Thickness of the line when drawing.
	*	@param in_radians If <em>true</em> all the angles of the window will be represented in radians, and all parameters involving angles must be in radians. The same applies when <em>false</em>, but with degrees instead of radians.
	*	@param log_size Size of the drawing log.
	*/
	void init(std::string window_title, int width, int height, RGBColor background_color, RGBColor drawing_color, double line_width, bool in_radians, size_t log_size);
	
	/** Initializes the Event mechanism.
	*/
	void eventInit();
	
	/** Destroys the Window and cleans all its allocated memory.
	*/
	void destroy();
	
	/** Copies all the configuration of @p w into this Window.
	*	@param w The Window that will be used as model.
	*/
	void copy(const Window & w);
	
	/** When called, the Window becomes the active display (only one Window can be set as active simultaneously).
	*/
	void checkActiveDisplay();
	
	/** Clears the Draw Log.
	*/
	void clearDrawLog();
	
	/** Changes the Window title.
	*	@param title New title.
	*/
	void setWindowTitle(std::string title);
	
	/** Returns the transformation needed to convert the custom view (0,0 at bottom left) of the Window to the Allegro mapping of the screen (0,0 at top left).
	*/
	ALLEGRO_TRANSFORM getDefaultTransform();
	
	/** Converts the user coordinates to Allegro-friendly coordinates.
	*	@param t Transformation to convert from user to Allegro coordinates.
	*	@param x X coordinate of the point to convert.
	*	@param y Y coordinate of the point to convert.
	*/
	void transformCoordinates(const ALLEGRO_TRANSFORM & t, float & x, float & y);
	
	/** Triggers Auto Update functionality. If Auto Update is enabled, it will update the screen. If not, it won't do anything.
	*/
	void autoUpdate();
	
	/** Triggers Auto Refresh functionality. If Auto Refresh is enabled, it will update the screen. If not, it won't do anything. This is similar to Auto Update functionality, but it's triggered only when the screen is maximized.
	*/
	void autoRefresh();
	
	/** Logs a Drawable action to the Draw Log.
	*	@param operation Drawable object that encapsulates a drawing action.
	*/
	void log(Drawable* operation);
	
	/** Redraws all the content of the Draw Log. Usually used when the screen is cleared.
	*/
	void redraw();
	
	/** Auxiliary function to add a Turtle to the Window's Turtle list (it isn't really a list, it's a map). 
	*	@param turtle_name Name of the Turtle.
	*	@param pen PaintBrush that the Turtle will use to draw its lines.
	*	@param start_point Point where the turtle will be spawned.
	*	@param font Font that the Turtle will use to draw text.
	*	@return A boolean value, <EM>true</EM> if the Turtle has been successfully added, false otherwise.
	*/
	bool addTurtleP(std::string turtle_name, PaintBrush pen, Point2D start_point, Font & font);
	
	/** This function is a little bit generic. Finds a Turtle in a TurtleMap and returns a pointer to it. With a little tweak it could be fully generic and find an element of a map and return a pointer to it.
	*/
	static Turtle* findTurtle(TurtleMap & turtle_map, MapKey turtle_name);
	
	/** This function is a little bit generic. Finds a Turtle in a TurtleMap and returns a const pointer to it. With a little tweak it could be fully generic and find an element of a map and return a const pointer to it.
	*/
	static const Turtle* peekTurtle(const TurtleMap & turtle_map, MapKey turtle_name);
	
	/** Same as the Turtle one, but with Fonts. Finds a Font in a FontMap and returns a pointer to it.
	*/
	static Font* findFont(FontMap & font_map, MapKey font_name);
	
	/** Draws all the cursors from the Turtles that are showing its positions.
	*/
	void drawTurtleCursors();
	
	/** Auxiliary function to draw a rotated image.
	*	@param image Image to be drawn.
	*	@param cx X coordinate of the rotation point (relative to the image).
	*	@param cy Y coordinate of the rotation point (relative to the image).
	*	@param dx X coordinate of the point where bottom left corner will be drawn.
	*	@param dy Y coordinate of the point where bottom left corner will be drawn.
	*	@param angle Rotation angle.
	*	@param flags Flags for the bitmap drawing. Its value is <EM>0</EM> by default.
	*	@return A boolean value, <EM>true</EM> if the image has been successfully drawn, <em>false</em> otherwise.
	*/
	bool i_rotated_image(Image image, float cx, float cy, float dx, float dy, float angle, int flags);

	//Event handling
	
	/** Waits for the next ALLEGRO_EVENT, without filters.
	*	@return The first ALLEGRO_EVENT in the EventQueue of the Window.
	*/
	ALLEGRO_EVENT waitForEvent();
	
	/** Waits for the next ALLEGRO_EVENT with the type specified.
	*	@param ev_type Type of the target event.
	*	@return The first ALLEGRO_EVENT in the EventQueue of the Window with the same type as @p ev_type.
	*/
	ALLEGRO_EVENT waitForEvent(ALLEGRO_EVENT_TYPE ev_type);
	
	/** Waits for the next ALLEGRO_EVENT, without filters, until the first ALLEGRO_EVENT arrives or the timeout expires. 
	*	@param seconds Max seconds to wait for an event.
	*	@return The first ALLEGRO_EVENT in the EventQueue of the Window if any, or a ALLEGRO_EVENT_TIMER if the timeout expires.
	*/
	ALLEGRO_EVENT waitForEventTimed(float seconds);
	
	/** Waits for the next WindowEvent with the type specified by the user until the first WindowEvent arrives or the timeout expires. The events with different type are skipped and removed from the queue.
	*	@param ev_type Type of the target event.
	*	@param seconds Max seconds to wait for an event.
	*	@return The first WindowEvent in the EventQueue of the Window with the same type as @p ev_type.
	*/
	ALLEGRO_EVENT waitForEventTimed(ALLEGRO_EVENT_TYPE ev_type, float seconds);

	/** Converts a Point Array to a float array (for Allegro purposes).
	*	@param p_array Array of Point2D.
	*	@param p_length length of @p p_array.
	* 	@pre @p f_array must be at least 2 * @p p_length size
	*/
	float* pointArrayToFloatArray(const Point2D * p_array, int p_length);
	
	/** Adds 0.5 to @p x. See CORRECTION_FACTOR for more details.
	*	@param x number to be corrected.
	*/
	float correctCoordinates(float x);
	
	/** Converts the user coordinates to Allegro-friendly coordinates and can apply a correction to them if needed.
	*	@param t Transformation to convert from user to Allegro coordinates.
	*	@param x X coordinate of the point to convert.
	*	@param y Y coordinate of the point to convert.
	*	@param correct_coordinates If true, CORRECTION_FACTOR will be applied to both coordinates, otherwise it won't.
	*/
	void transformCoordinates(const ALLEGRO_TRANSFORM * t, float * x, float * y, bool correct_coordinates);
	
	/** Converts the user coordinates in the array to Allegro-friendly coordinates and can apply a correction to them if needed.
	*	@param t Transformation to convert from user to Allegro coordinates.
	*	@param points Array of X and Y coordinates to be converted.
	*	@param n_points @p points size.
	*	@param correct_coordinates If true, the CORRECTION_FACTOR will be applied. If false it won't.
	*	@pre @p n_points must be at less or equal to @p points size.
	*	@return An array of converted coordinates.
	*/
	float* getTransformedPoints(const ALLEGRO_TRANSFORM & t, const float * points, size_t n_points, bool correct_coordinates);

	std::string _windowTitle;			 /**< Title shown at the top of the window.*/
	ALLEGRO_DISPLAY * _display; 		/**< Pointer to the Allegro structure that contains the display and its configuration*/
	ALLEGRO_EVENT_QUEUE * _eventQueue; 	/**< Pointer to the Allegro structure containing the event queue of the window.*/

	//class descriptors
	int _minX, 					/**< Min X coordinate of the display */
		_minY, 					/**< Max X coordinate of the display */
		_maxX, 					/**< Min Y coordinate of the display */
		_maxY;					/**< Max Y coordinate of the display */
	int _angleConversionType; 	/**< Variable that defines if the Window is using radians or degrees to represent angles.*/

	//global parameters
	RGBColor _backgroundColor;	 	/**< Background color of the screen.*/
	PaintBrush _drawingBrush; 		/**< Drawing color of the Window*/
	ALLEGRO_TRANSFORM _transform; 	/**< Transformation needed to convert between Window's representation of coordinates to Allegro's representation.*/

	//class structures
	std::deque<Drawable*> _drawLog; /**< A queue that stores the drawing operations effectuated on the Window if Draw Log functionality is enabled.*/
	size_t _maxLogSize; 			/**< Max number of operations that Draw Log can save.*/

	//relative drawing (Turtle graphics)
	TurtleMap _turtles; 	/**< Map containing the Turtles of the Window.*/
	Turtle* _activeTurtle; 	/**< Pointer to the active Turtle.*/
	FontMap _fonts; 		/**< Map containing the Fonts of the Window.*/
	Font* _defaultFont;		/**< Pointer to the default Font of the Window.*/
	Font* _activeFont; 		/**< Pointer to the active Font of the Window.*/

	//flags
	bool _autoUpdate;		/**< Indicates if Auto Update functionality is enabled or disabled.*/
	bool _drawLogging;		/**< Indicates if Draw Log functionality is enabled or disabled.*/
	bool _autoRefresh;		/**< Indicates if Auto Refresh functionality is enabled or disabled.*/
	bool _turtleCursorMoved;/**< Indicates if any Turtle of the Map has moved.*/
	bool _switchedIn;		/**< Indicates if user has activated the screen. This happens when user minimizes and then maximizes, or simply switches between windows with Alt + Tab or clicking it with the mouse, for example. It indicates that the screen is fully visible again.*/
};

#endif
