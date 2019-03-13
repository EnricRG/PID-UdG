	#include "Window.h"
	#include "Exceptions.h"
	#include "Drawables.h"
	#include <allegro5/allegro_image.h>
	#include <allegro5/allegro_ttf.h>

	#include "Turtle.h"
	#include "Angle.h"
	#include "Figures.h"

	#include "CommonUtils.h"
	#include "assert.h"

	int Window::NUMBER_OF_DISPLAYS = 0;

	Window::Window(int width, int height, RGBColor background_color, RGBColor drawing_color, double line_width, bool in_radians, Font f, size_t log_size)
	{
		init("", width, height, background_color, drawing_color, line_width, in_radians, log_size);
	}

	Window::Window(std::string window_title, int width, int height, RGBColor background_color, RGBColor drawing_color, double line_width, bool in_radians, Font f, size_t log_size)
	{
		init(window_title, width, height, background_color, drawing_color, line_width, in_radians, log_size);
	}

	Window::Window(const Window & w)
	{
		copy(w);
	}

	Window::~Window()
	{
		destroy();
	}

	Window & Window::operator=(const Window & w)
	{
		if (this != &w) {
			NUMBER_OF_DISPLAYS++;	//to avoid Allegro uninitialization
			destroy();
			NUMBER_OF_DISPLAYS--;
			copy(w);
		}
		return *this;
	}



	void Window::pixel(float x, float y, RGBColor color)
	{
		float transformed_x = x, transformed_y = y;
		bool correct_coordinates = true;

		transformCoordinates(&_transform, &transformed_x, &transformed_y, correct_coordinates);

		checkActiveDisplay();

		al_draw_pixel(transformed_x, transformed_y, color.toAllegroColor());
		autoUpdate();

		if (_drawLogging) log(new DrawPixel(x, y, color));
	}

	void Window::line(float x1, float y1, float x2, float y2, RGBColor color, float thickness)
	{
		float transformed_x1 = x1, transformed_y1 = y1, transformed_x2 = x2, transformed_y2 = y2;
		bool correct_coordinates = true;

		transformCoordinates(&_transform, &transformed_x1, &transformed_y1, correct_coordinates);
		transformCoordinates(&_transform, &transformed_x2, &transformed_y2, correct_coordinates);

		checkActiveDisplay();

		al_draw_line(transformed_x1, transformed_y1, transformed_x2, transformed_y2, color.toAllegroColor(), thickness);
		autoUpdate();

		if (_drawLogging) log(new DrawLine(x1, y1, x2, y2, color, thickness));
	}

	void Window::triangle(float x1, float y1, float x2, float y2, float x3, float y3, RGBColor color, float thickness)
	{
		float transformed_x1 = x1, transformed_y1 = y1, transformed_x2 = x2, transformed_y2 = y2, transformed_x3 = x3, transformed_y3 = y3;
		bool correct_coordinates = true;

		transformCoordinates(&_transform, &transformed_x1, &transformed_y1, correct_coordinates);
		transformCoordinates(&_transform, &transformed_x2, &transformed_y2, correct_coordinates);
		transformCoordinates(&_transform, &transformed_x3, &transformed_y3, correct_coordinates);

		checkActiveDisplay();

		al_draw_triangle(transformed_x1, transformed_y1, transformed_x2, transformed_y2, transformed_x3, transformed_y3, color.toAllegroColor(), thickness);
		autoUpdate();

		if (_drawLogging) log(new DrawTriangle(x1, y1, x2, y2, x3, y3, color, thickness));
	}

	void Window::filled_triangle(float x1, float y1, float x2, float y2, float x3, float y3, RGBColor color)
	{
		float transformed_x1 = x1, transformed_y1 = y1, transformed_x2 = x2, transformed_y2 = y2, transformed_x3 = x3, transformed_y3 = y3;
		bool correct_coordinates = false;

		transformCoordinates(&_transform, &transformed_x1, &transformed_y1, correct_coordinates);
		transformCoordinates(&_transform, &transformed_x2, &transformed_y2, correct_coordinates);
		transformCoordinates(&_transform, &transformed_x3, &transformed_y3, correct_coordinates);

		checkActiveDisplay();

		al_draw_filled_triangle(transformed_x1, transformed_y1, transformed_x2, transformed_y2, transformed_x3, transformed_y3, color.toAllegroColor());
		autoUpdate();

		if (_drawLogging) log(new DrawFilledTriangle(x1, y1, x2, y2, x3, y3, color));
	}

	void Window::rectangle(float x1, float y1, float x2, float y2, RGBColor color, float thickness)
	{
		float transformed_x1 = x1, transformed_y1 = y1, transformed_x2 = x2, transformed_y2 = y2;
		bool correct_coordinates = true;

		transformCoordinates(&_transform, &transformed_x1, &transformed_y1, correct_coordinates);
		transformCoordinates(&_transform, &transformed_x2, &transformed_y2, correct_coordinates);

		checkActiveDisplay();

		al_draw_rectangle(transformed_x1, transformed_y1, transformed_x2, transformed_y2, color.toAllegroColor(), thickness);
		autoUpdate();

		if (_drawLogging) log(new DrawRectangle(x1, y1, x2, y2, color, thickness));
	}

	void Window::filled_rectangle(float x1, float y1, float x2, float y2, RGBColor color)
	{
		float transformed_x1 = x1, transformed_y1 = y1, transformed_x2 = x2, transformed_y2 = y2;
		bool correct_coordinates = false;

		transformCoordinates(&_transform, &transformed_x1, &transformed_y1, correct_coordinates);
		transformCoordinates(&_transform, &transformed_x2, &transformed_y2, correct_coordinates);

		checkActiveDisplay();

		al_draw_filled_rectangle(transformed_x1, transformed_y1, transformed_x2, transformed_y2, color.toAllegroColor());
		autoUpdate();

		if (_drawLogging) log(new DrawFilledRectangle(x1, y1, x2, y2, color));
	}

	void Window::rounded_rectangle(float x1, float y1, float x2, float y2, float rx, float ry, RGBColor color, float thickness)
	{
		float transformed_x1 = x1, transformed_y1 = y1, transformed_x2 = x2, transformed_y2 = y2;
		bool correct_coordinates = true;

		transformCoordinates(&_transform, &transformed_x1, &transformed_y1, correct_coordinates);
		transformCoordinates(&_transform, &transformed_x2, &transformed_y2, correct_coordinates);

		checkActiveDisplay();

		al_draw_rounded_rectangle(transformed_x1, transformed_y1, transformed_x2, transformed_y2, rx, ry, color.toAllegroColor(), thickness);
		autoUpdate();

		if (_drawLogging) log(new DrawRoundedRectangle(x1, y1, x2, y2, rx, ry, color, thickness));
	}

	void Window::filled_rounded_rectangle(float x1, float y1, float x2, float y2, float rx, float ry, RGBColor color)
	{
		float transformed_x1 = x1, transformed_y1 = y1, transformed_x2 = x2, transformed_y2 = y2;
		bool correct_coordinates = false;

		transformCoordinates(&_transform, &transformed_x1, &transformed_y1, correct_coordinates);
		transformCoordinates(&_transform, &transformed_x2, &transformed_y2, correct_coordinates);

		checkActiveDisplay();

		al_draw_filled_rounded_rectangle(transformed_x1, transformed_y1, transformed_x2, transformed_y2, rx, ry, color.toAllegroColor());
		autoUpdate();

		if (_drawLogging) log(new DrawFilledRoundedRectangle(x1, y1, x2, y2, rx, ry, color));
	}

	void Window::quadrilateral(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, RGBColor color, float thickness)
	{
		float vertices[8] = { x1,y1,x2,y2,x3,y3,x4,y4 };
		polygon(vertices, 4, color, thickness);
	}

	void Window::filled_quadrilateral(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, RGBColor color)
	{
		float vertices[8] = { x1,y1,x2,y2,x3,y3,x4,y4 };
		filled_polygon(vertices, 4, color);
	}

	void Window::ellipse(float cx, float cy, float rx, float ry, RGBColor color, float thickness)
	{
		float transformed_cx = cx, transformed_cy = cy;
		bool correct_coordinates = true;

		transformCoordinates(&_transform, &transformed_cx, &transformed_cy, correct_coordinates);

		checkActiveDisplay();

		al_draw_ellipse(transformed_cx, transformed_cy, rx, ry, color.toAllegroColor(), thickness);
		autoUpdate();

		if (_drawLogging) log(new DrawEllipse(cx, cy, rx, ry, color, thickness));
	}

	void Window::filled_ellipse(float cx, float cy, float rx, float ry, RGBColor color)
	{
		float transformed_cx = cx, transformed_cy = cy;
		bool correct_coordinates = false;

		transformCoordinates(&_transform, &transformed_cx, &transformed_cy, correct_coordinates);

		checkActiveDisplay();

		al_draw_filled_ellipse(transformed_cx, transformed_cy, rx, ry, color.toAllegroColor());
		autoUpdate();

		if (_drawLogging) log(new DrawFilledEllipse(cx, cy, rx, ry, color));
	}

	void Window::circle(float cx, float cy, float r, RGBColor color, float thickness)
	{
		float transformed_cx = cx, transformed_cy = cy;
		bool correct_coordinates = true;

		transformCoordinates(&_transform, &transformed_cx, &transformed_cy, correct_coordinates);

		checkActiveDisplay();

		al_draw_circle(transformed_cx, transformed_cy, r, color.toAllegroColor(), thickness);
		autoUpdate();

		if (_drawLogging) log(new DrawCircle(cx, cy, r, color, thickness));
	}

	void Window::filled_circle(float cx, float cy, float r, RGBColor color)
	{
		float transformed_cx = cx, transformed_cy = cy;
		bool correct_coordinates = false;

		transformCoordinates(&_transform, &transformed_cx, &transformed_cy, correct_coordinates);

		checkActiveDisplay();

		al_draw_filled_circle(transformed_cx, transformed_cy, r, color.toAllegroColor());
		autoUpdate();

		if (_drawLogging) log(new DrawFilledCircle(cx, cy, r, color));
	}

	void Window::arc(float cx, float cy, float r, float start_theta, float delta_theta, RGBColor color, float thickness)
	{
		float transformed_cx = cx, transformed_cy = cy;
		bool correct_coordinates = true;

		transformCoordinates(&_transform, &transformed_cx, &transformed_cy, correct_coordinates);

		Angle a(start_theta, delta_theta, _angleConversionType); //struct that stores and allows conversion between different angle representations

		checkActiveDisplay();

		al_draw_arc(transformed_cx, transformed_cy, r, -a.start, -a.delta, color.toAllegroColor(), thickness); //negative angles for convenience (unit circle)
		autoUpdate();

		if (_drawLogging) log(new DrawArc(cx, cy, r, Angle(start_theta, delta_theta, NO_CONVERSION), color, thickness));
	}

	void Window::elliptical_arc(float cx, float cy, float rx, float ry, float start_theta, float delta_theta, RGBColor color, float thickness)
	{
		float transformed_cx = cx, transformed_cy = cy;
		bool correct_coordinates = true;

		transformCoordinates(&_transform, &transformed_cx, &transformed_cy, correct_coordinates);

		Angle a(start_theta, delta_theta, _angleConversionType); //struct that stores and allows conversion between different angle representations

		checkActiveDisplay();

		al_draw_elliptical_arc(transformed_cx, transformed_cy, rx, ry, -a.start, -a.delta, color.toAllegroColor(), thickness); //negative angles for convenience (unit circle)
		autoUpdate();

		if (_drawLogging) log(new DrawEllipticalArc(cx, cy, rx, ry, Angle(start_theta, delta_theta, NO_CONVERSION), color, thickness));
	}

	void Window::pieslice(float cx, float cy, float r, float start_theta, float delta_theta, RGBColor color, float thickness)
	{
		float transformed_cx = cx, transformed_cy = cy;
		bool correct_coordinates = true;

		transformCoordinates(&_transform, &transformed_cx, &transformed_cy, correct_coordinates);

		Angle a(start_theta, delta_theta, _angleConversionType); //struct that stores and allows conversion between different angle representations

		checkActiveDisplay();

		al_draw_pieslice(transformed_cx, transformed_cy, r, -a.start, -a.delta, color.toAllegroColor(), thickness); //negative angles for convenience (unit circle)
		autoUpdate();

		if (_drawLogging) log(new DrawPieslice(cx, cy, r, Angle(start_theta, delta_theta, NO_CONVERSION), color, thickness));
	}

	void Window::filled_pieslice(float cx, float cy, float r, float start_theta, float delta_theta, RGBColor color)
	{
		float transformed_cx = cx, transformed_cy = cy;
		bool correct_coordinates = false;

		transformCoordinates(&_transform, &transformed_cx, &transformed_cy, correct_coordinates);

		Angle a(start_theta, delta_theta, _angleConversionType); //struct that stores and allows conversion between different angle representations

		checkActiveDisplay();

		al_draw_filled_pieslice(transformed_cx, transformed_cy, r, -a.start, -a.delta, color.toAllegroColor()); //negative angles for convenience (unit circle)
		autoUpdate();

		if (_drawLogging) log(new DrawFilledPieslice(cx, cy, r, Angle(start_theta, delta_theta, NO_CONVERSION), color));
	}

	void Window::spline(float points[8], RGBColor color, float thickness)
	{
		bool correct_coordinates = true;
		float* transformed_points = getTransformedPoints(_transform, points, 8, correct_coordinates);

		checkActiveDisplay();

		al_draw_spline(transformed_points, color.toAllegroColor(), thickness);

		delete transformed_points;

		autoUpdate();

		if (_drawLogging) log(new DrawSpline(points, color, thickness));
	}

	void Window::ribbon(const float * points, int num_points, RGBColor color, float thickness)
	{
		bool correct_coordinates = true;
		float* transformed_points = getTransformedPoints(_transform, points, (num_points+1)*2, correct_coordinates);

		checkActiveDisplay();

		al_draw_ribbon(transformed_points, POINTS_STRIDE, color.toAllegroColor(), thickness, num_points);

		delete transformed_points;

		autoUpdate();

		if (_drawLogging) log(new DrawRibbon(points, num_points, color, thickness));
	}

	void Window::text(Font & font, float x, float y, std::string text, int flags)
	{
		ALLEGRO_FONT* al_font = font.font;
		if (!al_font) throw WindowException("Could not load font from path " + font.fontPath);

		float transformed_x = x, transformed_y = y;
		bool correct_coordinates = false;

		transformCoordinates(&_transform, &transformed_x, &transformed_y, correct_coordinates);

		checkActiveDisplay();

		al_draw_multiline_text(al_font, font.color.toAllegroColor(), transformed_x, transformed_y, _maxX, font.size, flags, text.c_str());
		
		autoUpdate();

		if (_drawLogging) log(new DrawText(font, Point2D(x,y), text, flags));
	}

	void Window::text(std::string font_name, float x, float y, std::string text, int flags)
	{
		this->text(*findFont(_fonts, font_name), x, y, text, flags);
	}

	void Window::polyline(const float * vertices, int vertex_count, RGBColor color, float thickness, int join_style, int cap_style, float miter_limit)
	{
		bool correct_coordinates = true;
		float* transformed_points = getTransformedPoints(_transform, vertices, 2*vertex_count, correct_coordinates);

		checkActiveDisplay();

		al_draw_polyline(transformed_points, POINTS_STRIDE, vertex_count, join_style, cap_style, color.toAllegroColor(), thickness, miter_limit);

		delete transformed_points;

		autoUpdate();

		if (_drawLogging) log(new DrawPolyline(vertices, vertex_count, color, thickness));
	}

	void Window::polygon(const float * vertices, int vertex_count, RGBColor color, float thickness, int join_style, float miter_limit)
	{
		bool correct_coordinates = true;
		float* transformed_points = getTransformedPoints(_transform, vertices, 2*vertex_count, correct_coordinates);

		checkActiveDisplay();

		al_draw_polygon(transformed_points, vertex_count, join_style, color.toAllegroColor(), thickness, miter_limit);

		delete transformed_points;

		autoUpdate();

		if (_drawLogging) log(new DrawPolygon(vertices, vertex_count, color, thickness));
	}

	void Window::filled_polygon(const float * vertices, int vertex_count, RGBColor color)
	{
		bool correct_coordinates = true;
		float* transformed_points = getTransformedPoints(_transform, vertices, 2*vertex_count, correct_coordinates);

		checkActiveDisplay();

		al_draw_filled_polygon(transformed_points, vertex_count, color.toAllegroColor());

		delete transformed_points;

		autoUpdate();

		if (_drawLogging) log(new DrawFilledPolygon(vertices, vertex_count, color));
	}

	void Window::filled_polygon_with_holes(const float * vertices, const int * vertex_counts, RGBColor color)
	{
		bool correct_coordinates = true;
		float* transformed_points = getTransformedPoints(_transform, vertices, 2*intArraySum(vertex_counts), correct_coordinates);

		checkActiveDisplay();

		al_draw_filled_polygon_with_holes(transformed_points, vertex_counts, color.toAllegroColor());

		delete transformed_points;

		autoUpdate();

		if (_drawLogging) log(new DrawFilledPolygonWithHoles(vertices, vertex_counts, color));
	}



	void Window::pixel(Point2D p, RGBColor color)
	{
		pixel(p.x, p.y, color);
	}

	void Window::line(Point2D p1, Point2D p2, RGBColor color, float thickness)
	{
		line(p1.x, p1.y, p2.x, p2.y, color, thickness);
	}

	void Window::triangle(Point2D p1, Point2D p2, Point2D p3, RGBColor color, float thickness)
	{
		triangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, color, thickness);
	}

	void Window::filled_triangle(Point2D p1, Point2D p2, Point2D p3, RGBColor color)
	{
		filled_triangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, color);
	}

	void Window::rectangle(Point2D p1, Point2D p2, RGBColor color, float thickness)
	{
		rectangle(p1.x, p1.y, p2.x, p2.y, color, thickness);
	}

	void Window::filled_rectangle(Point2D p1, Point2D p2, RGBColor color)
	{
		filled_rectangle(p1.x, p1.y, p2.x, p2.y, color);
	}

	void Window::rounded_rectangle(Point2D p1, Point2D p2, float rx, float ry, RGBColor color, float thickness)
	{
		rounded_rectangle(p1.x, p1.y, p2.x, p2.y, rx, ry, color, thickness);
	}

	void Window::filled_rounded_rectangle(Point2D p1, Point2D p2, float rx, float ry, RGBColor color)
	{
		filled_rounded_rectangle(p1.x, p1.y, p2.x, p2.y, rx, ry, color);
	}

	void Window::quadrilateral(Point2D p1, Point2D p2, Point2D p3, Point2D p4, RGBColor color, float thickness)
	{
		quadrilateral(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y, color, thickness);
	}

	void Window::filled_quadrilateral(Point2D p1, Point2D p2, Point2D p3, Point2D p4, RGBColor color)
	{
		filled_quadrilateral(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y, color);
	}

	void Window::ellipse(Point2D c, float rx, float ry, RGBColor color, float thickness)
	{
		ellipse(c.x, c.y, rx, ry, color, thickness);
	}

	void Window::filled_ellipse(Point2D c, float rx, float ry, RGBColor color)
	{
		filled_ellipse(c.x, c.y, rx, ry, color);
	}

	void Window::circle(Point2D c, float r, RGBColor color, float thickness)
	{
		circle(c.x, c.y, r, color, thickness);
	}

	void Window::filled_circle(Point2D c, float r, RGBColor color)
	{
		filled_circle(c.x, c.y, r, color);
	}

	void Window::arc(Point2D c, float r, float start_theta, float delta_theta, RGBColor color, float thickness)
	{
		arc(c.x, c.y, r, start_theta, delta_theta, color, thickness);
	}

	void Window::elliptical_arc(Point2D c, float rx, float ry, float start_theta, float delta_theta, RGBColor color, float thickness)
	{
		elliptical_arc(c.x, c.y, rx, ry, start_theta, delta_theta, color, thickness);
	}

	void Window::pieslice(Point2D c, float r, float start_theta, float delta_theta, RGBColor color, float thickness)
	{
		pieslice(c.x, c.y, r, start_theta, delta_theta, color, thickness);
	}

	void Window::filled_pieslice(Point2D c, float r, float start_theta, float delta_theta, RGBColor color)
	{
		filled_pieslice(c.x, c.y, r, start_theta, delta_theta, color);
	}

	void Window::spline(Point2D points[4], RGBColor color, float thickness)
	{
		float* float_points = pointArrayToFloatArray(points, 4);
		spline(float_points, color, thickness);
		delete float_points;
	}

	void Window::ribbon(const Point2D * points, int num_points, RGBColor color, float thickness)
	{
		int n_points = num_points + 1;
		float* float_points = pointArrayToFloatArray(points, n_points);
		ribbon(float_points, num_points, color, thickness);
		delete float_points;
	}

	void Window::text(Font & font, Point2D p, std::string text, int flags)
	{
		this->text(font, p.x, p.y, text, flags);
	}

	void Window::text(std::string font_name, Point2D p, std::string text, int flags)
	{
		this->text(*findFont(_fonts, font_name), p, text, flags);
	}

	void Window::polyline(const Point2D * vertices, int vertex_count, RGBColor color, float thickness, int join_style, int cap_style, float miter_limit)
	{
		float* float_vertices = pointArrayToFloatArray(vertices, vertex_count);
		polyline(float_vertices, vertex_count, color, thickness, join_style, cap_style, miter_limit);
		delete float_vertices;
	}

	void Window::polygon(const Point2D * vertices, int vertex_count, RGBColor color, float thickness, int join_style, float miter_limit)
	{
		float* float_vertices = pointArrayToFloatArray(vertices, vertex_count);
		polygon(float_vertices, vertex_count, color, thickness, join_style, miter_limit);
		delete float_vertices;
	}

	void Window::filled_polygon(const Point2D * vertices, int vertex_count, RGBColor color)
	{
		float* float_vertices = pointArrayToFloatArray(vertices, vertex_count);
		filled_polygon(float_vertices, vertex_count, color);
		delete float_vertices;
	}

	void Window::filled_polygon_with_holes(const Point2D * vertices, const int * vertex_counts, RGBColor color)
	{
		int n_points = intArraySum(vertex_counts);
		float* float_vertices = pointArrayToFloatArray(vertices, n_points);
		filled_polygon_with_holes(float_vertices, vertex_counts, color);
		delete float_vertices;
	}



	void Window::pixel(float x, float y)
	{
		pixel(x, y, _drawingBrush.color);
	}

	void Window::line(float x1, float y1, float x2, float y2)
	{
		line(x1, y1, x2, y2, _drawingBrush.color, _drawingBrush.thickness);
	}

	void Window::triangle(float x1, float y1, float x2, float y2, float x3, float y3)
	{
		triangle(x1, y1, x2, y2, x3, y3, _drawingBrush.color, _drawingBrush.thickness);
	}

	void Window::filled_triangle(float x1, float y1, float x2, float y2, float x3, float y3)
	{
		filled_triangle(x1, y1, x2, y2, x3, y3, _drawingBrush.color);
	}

	void Window::rectangle(float x1, float y1, float x2, float y2)
	{
		rectangle(x1, y1, x2, y2, _drawingBrush.color, _drawingBrush.thickness);
	}

	void Window::filled_rectangle(float x1, float y1, float x2, float y2)
	{
		filled_rectangle(x1, y1, x2, y2, _drawingBrush.color);
	}

	void Window::rounded_rectangle(float x1, float y1, float x2, float y2, float rx, float ry)
	{
		rounded_rectangle(x1, y1, x2, y2, rx, ry, _drawingBrush.color, _drawingBrush.thickness);
	}

	void Window::filled_rounded_rectangle(float x1, float y1, float x2, float y2, float rx, float ry)
	{
		filled_rounded_rectangle(x1, y1, x2, y2, rx, ry, _drawingBrush.color);
	}

	void Window::quadrilateral(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
	{
		quadrilateral(x1, y1, x2, y2, x3, y3, x4, y4, _drawingBrush.color, _drawingBrush.thickness);
	}

	void Window::filled_quadrilateral(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
	{
		filled_quadrilateral(x1, y1, x2, y2, x3, y3, x4, y4, _drawingBrush.color);
	}

	void Window::ellipse(float cx, float cy, float rx, float ry)
	{
		ellipse(cx, cy, rx, ry, _drawingBrush.color, _drawingBrush.thickness);
	}

	void Window::filled_ellipse(float cx, float cy, float rx, float ry)
	{
		filled_ellipse(cx, cy, rx, ry, _drawingBrush.color);
	}

	void Window::circle(float cx, float cy, float r)
	{
		circle(cx, cy, r, _drawingBrush.color, _drawingBrush.thickness);
	}

	void Window::filled_circle(float cx, float cy, float r)
	{
		filled_circle(cx, cy, r, _drawingBrush.color);
	}

	void Window::arc(float cx, float cy, float r, float start_theta, float delta_theta)
	{
		arc(cx, cy, r, start_theta, delta_theta, _drawingBrush.color, _drawingBrush.thickness);
	}

	void Window::elliptical_arc(float cx, float cy, float rx, float ry, float start_theta, float delta_theta)
	{
		elliptical_arc(cx, cy, rx, ry, start_theta, delta_theta, _drawingBrush.color, _drawingBrush.thickness);
	}

	void Window::pieslice(float cx, float cy, float r, float start_theta, float delta_theta)
	{
		pieslice(cx, cy, r, start_theta, delta_theta, _drawingBrush.color, _drawingBrush.thickness);
	}

	void Window::filled_pieslice(float cx, float cy, float r, float start_theta, float delta_theta)
	{
		filled_pieslice(cx, cy, r, start_theta, delta_theta, _drawingBrush.color);
	}

	void Window::spline(float points[8])
	{
		spline(points, _drawingBrush.color, _drawingBrush.thickness);
	}

	void Window::ribbon(const float * points, int num_points)
	{
		ribbon(points, num_points, _drawingBrush.color, _drawingBrush.thickness);
	}

	void Window::text(float x, float y, std::string text, int flags)
	{
		this->text(*_activeFont, x, y, text.c_str(), flags);
	}

	void Window::polyline(const float * vertices, int vertex_count, int join_style, int cap_style, float miter_limit)
	{
		polyline(vertices, vertex_count, _drawingBrush.color, _drawingBrush.thickness, join_style, cap_style, miter_limit);
	}

	void Window::polygon(const float * vertices, int vertex_count, int join_style, float miter_limit)
	{
		polygon(vertices, vertex_count, _drawingBrush.color, _drawingBrush.thickness, join_style, miter_limit);
	}

	void Window::filled_polygon(const float * vertices, int vertex_count)
	{
		filled_polygon(vertices, vertex_count, _drawingBrush.color);
	}

	void Window::filled_polygon_with_holes(const float * vertices, const int * vertex_counts)
	{
		filled_polygon_with_holes(vertices, vertex_counts, _drawingBrush.color);
	}



	void Window::pixel(Point2D p)
	{
		pixel(p, _drawingBrush.color);
	}

	void Window::line(Point2D p1, Point2D p2)
	{
		line(p1, p2, _drawingBrush.color, _drawingBrush.thickness);
	}

	void Window::triangle(Point2D p1, Point2D p2, Point2D p3)
	{
		triangle(p1, p2, p3, _drawingBrush.color, _drawingBrush.thickness);
	}

	void Window::filled_triangle(Point2D p1, Point2D p2, Point2D p3)
	{
		filled_triangle(p1,p2,p3,_drawingBrush.color);
	}

	void Window::rectangle(Point2D p1, Point2D p2)
	{
		rectangle(p1, p2, _drawingBrush.color, _drawingBrush.thickness);
	}

	void Window::filled_rectangle(Point2D p1, Point2D p2)
	{
		filled_rectangle(p1, p2, _drawingBrush.color);
	}

	void Window::rounded_rectangle(Point2D p1, Point2D p2, float rx, float ry)
	{
		rounded_rectangle(p1, p2, rx, ry, _drawingBrush.color, _drawingBrush.thickness);
	}

	void Window::quadrilateral(Point2D p1, Point2D p2, Point2D p3, Point2D p4)
	{
		quadrilateral(p1, p2, p3, p4, _drawingBrush.color, _drawingBrush.thickness);
	}

	void Window::filled_quadrilateral(Point2D p1, Point2D p2, Point2D p3, Point2D p4)
	{
		filled_quadrilateral(p1, p2, p3, p4, _drawingBrush.color);
	}

	void Window::filled_rounded_rectangle(Point2D p1, Point2D p2, float rx, float ry)
	{
		filled_rounded_rectangle(p1, p2, rx, ry, _drawingBrush.color);
	}

	void Window::ellipse(Point2D c, float rx, float ry)
	{
		ellipse(c, rx, ry, _drawingBrush.color, _drawingBrush.thickness);
	}

	void Window::filled_ellipse(Point2D c, float rx, float ry)
	{
		filled_ellipse(c, rx, ry, _drawingBrush.color);
	}

	void Window::circle(Point2D c, float r)
	{
		circle(c, r, _drawingBrush.color, _drawingBrush.thickness);
	}

	void Window::filled_circle(Point2D c, float r)
	{
		filled_circle(c, r, _drawingBrush.color);
	}

	void Window::arc(Point2D c, float r, float start_theta, float delta_theta)
	{
		arc(c, r, start_theta, delta_theta, _drawingBrush.color, _drawingBrush.thickness);
	}

	void Window::elliptical_arc(Point2D c, float rx, float ry, float start_theta, float delta_theta)
	{
		elliptical_arc(c, rx, ry, start_theta, delta_theta, _drawingBrush.color, _drawingBrush.thickness);
	}

	void Window::pieslice(Point2D c, float r, float start_theta, float delta_theta)
	{
		pieslice(c, r, start_theta, delta_theta, _drawingBrush.color, _drawingBrush.thickness);
	}

	void Window::filled_pieslice(Point2D c, float r, float start_theta, float delta_theta)
	{
		filled_pieslice(c, r, start_theta, delta_theta, _drawingBrush.color);
	}

	void Window::spline(Point2D points[4])
	{
		spline(points, _drawingBrush.color, _drawingBrush.thickness);
	}

	void Window::ribbon(const Point2D * points, int num_points)
	{
		ribbon(points, num_points, _drawingBrush.color, _drawingBrush.thickness);
	}

	void Window::text(Point2D p, std::string text, int flags)
	{
		this->text(*_activeFont, p, text.c_str(), flags);
	}

	void Window::polyline(const Point2D * vertices, int vertex_count, int join_style, int cap_style, float miter_limit)
	{
		polyline(vertices, vertex_count, _drawingBrush.color, _drawingBrush.thickness, join_style, cap_style, miter_limit);
	}

	void Window::polygon(const Point2D * vertices, int vertex_count, int join_style, float miter_limit)
	{
		polygon(vertices, vertex_count, _drawingBrush.color, _drawingBrush.thickness, join_style, miter_limit);
	}

	void Window::filled_polygon(const Point2D * vertices, int vertex_count)
	{
		filled_polygon(vertices, vertex_count, _drawingBrush.color);
	}

	void Window::filled_polygon_with_holes(const Point2D * vertices, const int * vertex_counts)
	{
		filled_polygon_with_holes(vertices, vertex_counts, _drawingBrush.color);
	}


	
	void Window::draw(Drawable * draw_target)
	{
		bool autoUpdate = _autoUpdate;
		disableAutoUpdate();

		checkActiveDisplay();

		draw_target->draw(*this);

		_autoUpdate = autoUpdate;
		this->autoUpdate();
	}

	void Window::draw(Drawable** draw_target, size_t size)
	{
		bool autoUpdate = _autoUpdate;
		disableAutoUpdate();

		checkActiveDisplay();

		for (size_t i = 0; i < size; i++) draw_target[i]->draw(*this);

		_autoUpdate = autoUpdate;
		this->autoUpdate();
	}

	
	void Window::rest(float time) {
		if (time < 0) WindowException("Time cannot be negative, or can it?");
		else {
			checkActiveDisplay();
			al_rest(time);
		}
	}

	void Window::update()
	{
		checkActiveDisplay();

		if (_turtleCursorMoved || _switchedIn) {
			_switchedIn = false;

 			ALLEGRO_BITMAP* screen_state = al_clone_bitmap(al_get_backbuffer(_display));

			drawTurtleCursors();

			al_flip_display();

			al_draw_bitmap(screen_state, 0, 0, 0);
			_turtleCursorMoved = false;

			al_destroy_bitmap(screen_state);
		}
		else {
			////
			ALLEGRO_BITMAP* b= al_get_target_bitmap();
			if (!b) throw "stringo";
			////
			al_flip_display();
		}
	}

	void Window::clear()
	{
		checkActiveDisplay();

		al_clear_to_color(_backgroundColor.toAllegroColor());
		autoUpdate();
		clearDrawLog();
	}

	void Window::enableAutoUpdate()
	{
		_autoUpdate = true;
	}

	void Window::disableAutoUpdate()
	{
		_autoUpdate = false;
	}

	void Window::enableLogging()
	{
		_drawLogging = true;
	}

	void Window::disableLogging()
	{
		_drawLogging = false;
	}

	void Window::hideCursor()
	{
		al_hide_mouse_cursor(_display);
	}

	void Window::showCursor()
	{
		al_show_mouse_cursor(_display);
	}

	void Window::useRadians()
	{
		_angleConversionType = NO_CONVERSION;
	}

	void Window::useDegrees()
	{
		_angleConversionType = DEGS_TO_RADS;
	}

	void Window::changeBackgroundColor(int r, int g, int b, int a)
	{
		changeBackgroundColor(RGBColor(r, g, b, a));
	}

	void Window::changeBackgroundColor(RGBColor c)
	{
		checkActiveDisplay();

		_backgroundColor = c;
		al_clear_to_color(_backgroundColor.toAllegroColor());
		redraw();
		turtleMoved();
		update();
	}

	void Window::changeDrawingColor(int r, int g, int b, int a)
	{
		changeDrawingColor(RGBColor(r, g, b, a));
	}

	void Window::changeDrawingColor(RGBColor c)
	{
		_drawingBrush.color = c;
	}

	void Window::changeDrawingThickness(float thickness)
	{
		_drawingBrush.thickness = thickness;
	}



	bool Window::addFont(std::string font_name, std::string font_path, RGBColor color, int size, int flags)
	{
		if (font_name == "") throw WindowException("A font must have a non empty string as a name");

		Font f(font_path, color, size, flags);
		std::pair<FontMap::iterator, bool> insert = _fonts.insert(FontMapElement(font_name, f));
		return insert.second;
	}

	bool Window::addFont(std::string font_name, Font & f)
	{
		if (font_name == "") throw WindowException("A font must have a non empty string as a name");

		std::pair<FontMap::iterator, bool> insert = _fonts.insert(FontMapElement(font_name, f));
		return insert.second;
	}

	bool Window::deleteFont(std::string font_name)
	{
		if(font_name != DEFAULT_FONT_NAME)
			return (_turtles.erase(font_name))>0; //if at least one element is erased
		return false;
	}

	Font Window::getActiveFont() const
	{
		return *_activeFont;
	}

	Font Window::getDefaultFont() const
	{
		return *_defaultFont;
	}

	bool Window::setActiveFont(std::string font_name)
	{
		FontMap::iterator it = _fonts.find(font_name);
		if (it != _fonts.end()) {
			_activeFont = &it->second;
			return true;
		}
		else return false;
	}

	size_t Window::nFonts() const
	{
		return _fonts.size();
	}



	Image Window::loadImage(std::string file_path)
	{
		return Image(file_path);
	}

	bool Window::saveToFile(std::string save_path, std::string extension)
	{
		std::string complete_path = save_path + "." + extension;

		checkActiveDisplay();

		ALLEGRO_BITMAP* display_image = al_get_backbuffer(_display);
		return al_save_bitmap(complete_path.c_str(), display_image);
	}

	bool Window::image(Image image, float x, float y, int flags)
	{
		if (image.isInvalid()) return false;

		float transformed_x = x, transformed_y = y + image.height();
		bool correct_coordinates = false;

		transformCoordinates(&_transform, &transformed_x, &transformed_y, correct_coordinates);

		checkActiveDisplay();

		al_draw_bitmap(image.image, transformed_x, transformed_y, flags);

		autoUpdate();

		if (_drawLogging) log(new DrawImage(image, x, y, flags));

		return true;
	}

	bool Window::image(Image image, Point2D p, int flags)
	{
		return this->image(image, p.x, p.y, flags);
	}

	bool Window::image(std::string file_path, float x, float y, int flags)
	{
		Image image(file_path.c_str());
		return this->image(image, x, y, flags);
	}

	bool Window::image(std::string file_path, Point2D p, int flags)
	{
		return image(file_path, p.x, p.y, flags);
	}

	bool Window::rotated_image(Image image, float cx, float cy, float dx, float dy, float angle, int flags)
	{
		Angle a(0, angle, _angleConversionType); //struct that stores and allows conversion between different angle representations
		return i_rotated_image(image, cx, cy, dx, dy, a.delta, flags);
	}

	bool Window::rotated_image(Image image, Point2D c, Point2D d, float angle, int flags)
	{
		return rotated_image(image, c.x, c.y, d.x, d.y, angle, flags);
	}

	bool Window::rotated_image(std::string file_path, float cx, float cy, float dx, float dy, float angle, int flags)
	{
		Image i(file_path);
		return rotated_image(i, cx, cy, dx, dy, angle, flags);
	}

	bool Window::rotated_image(std::string file_path, Point2D c, Point2D d, float angle, int flags)
	{
		return rotated_image(file_path, c.x, c.y, d.x, d.y, angle, flags);
	}



	bool Window::addTurtle(std::string turtle_name)
	{
		return addTurtleP(turtle_name, _drawingBrush, Point2D(0, 0), *_activeFont);
	}

	bool Window::addTurtle(std::string turtle_name, PaintBrush pen)
	{
		return addTurtleP(turtle_name, pen, Point2D(0, 0), *_activeFont);
	}

	bool Window::addTurtle(std::string turtle_name, PaintBrush pen, Point2D start_point)
	{
		return addTurtleP(turtle_name, pen, start_point, *_activeFont);
	}

	bool Window::addTurtle(std::string turtle_name, PaintBrush pen, Point2D start_point, Font & font)
	{
		return addTurtleP(turtle_name, pen, start_point, font);
	}

	bool Window::releaseTurtle(std::string turtle_name)
	{
		if(turtle_name != DEFAULT_TURTLE_NAME)
			return (_turtles.erase(turtle_name))>0; //if at least one element is erased
		return false;
	}

	std::string Window::activeTurtle() const
	{
		return _activeTurtle->getName();
	}

	bool Window::setActiveTurtle(std::string turtle_name)
	{
		TurtleMap::iterator it = _turtles.find(turtle_name);
		if (it != _turtles.end()) {
			_activeTurtle = &it->second;
			return true;
		}
		else return false;
	}

	size_t Window::nTurtles() const
	{
		return _turtles.size();
	}



	std::string Window::t_getName() const
	{
		return _activeTurtle->getName();
	}

	float Window::t_heading() const
	{
		Angle a(0, _activeTurtle->heading(), RADS_TO_DEGS); //turtle heading is always in rads, so we convert it to degs
		return a.delta;
	}

	Point2D Window::t_getPos() const
	{
		return _activeTurtle->getPos();
	}

	float Window::t_getPosX() const
	{
		return t_getPos().x;
	}

	float Window::t_getPosY() const
	{
		return t_getPos().y;
	}

	Point2D Window::t_forward(float dist)
	{
		return _activeTurtle->forward(dist);
	}

	Point2D Window::t_back(float dist)
	{
		return _activeTurtle->back(dist);
	}

	float Window::t_left(float angle)
	{
		Angle a(0, angle, _angleConversionType);
		return _activeTurtle->left(a.delta);
	}

	float Window::t_right(float angle)
	{
		Angle a(0, angle, _angleConversionType);
		return _activeTurtle->right(a.delta);
	}

	Point2D Window::t_setPos(float x, float y)
	{
		return _activeTurtle->setPos(x,y);
	}

	Point2D Window::t_setPos(Point2D p)
	{
		return _activeTurtle->setPos(p);
	}

	float Window::t_setHeading(float angle)
	{
		Angle a(0, angle, _angleConversionType);
		return _activeTurtle->setHeading(a.delta);
	}

	RGBColor Window::t_setDrawingColor(RGBColor color)
	{
		return _activeTurtle->setDrawingColor(color);
	}

	RGBColor Window::t_setDrawingColor(int r, int g, int b, int a)
	{
		return t_setDrawingColor(RGBColor(r, g, b, a));
	}

	float Window::t_setDrawingThickness(float thickness)
	{
		return _activeTurtle->setDrawingThickness(thickness);
	}

	PaintBrush Window::t_setPen(PaintBrush pen)
	{
		return _activeTurtle->setPen(pen);
	}

	RGBColor Window::t_setPen(RGBColor color)
	{
		return t_setPen(color, _drawingBrush.thickness);
	}

	RGBColor Window::t_setPen(RGBColor color, float thickness)
	{
		return t_setPen(PaintBrush(color, thickness)).color;
	}

	Point2D Window::t_home()
	{
		return _activeTurtle->setPos(TURTLE_HOME);
	}

	void Window::t_show()
	{
		_activeTurtle->show();
	}

	void Window::t_hide()
	{
		_activeTurtle->hide();
	}

	void Window::t_penUp()
	{
		_activeTurtle->penUp();
	}

	void Window::t_penDown()
	{
		_activeTurtle->penDown();
	}

	void Window::t_swapPen()
	{
		_activeTurtle->swapPen();
	}

	void Window::t_label(std::string text, int flags)
	{
		_activeTurtle->label(text.c_str(), flags);
	}

	void Window::t_label(Font f, std::string text, int flags)
	{
		_activeTurtle->label(f, text, flags);
	}

	void Window::t_image(Image i, int flags)
	{
		_activeTurtle->image(i, flags);
	}

	void Window::t_image(std::string image_path, int flags)
	{
		_activeTurtle->image(image_path, flags);
	}

	void Window::t_changeMotion(int turtle_motion)
	{
		_activeTurtle->changeMotion(turtle_motion);
	}

	void Window::t_setFont(Font f)
	{
		_activeTurtle->setFont(f);
	}

	void Window::t_changeCursorColor(RGBColor color)
	{
		_activeTurtle->changeCursorColor(color);
	}

	std::string Window::t_getName(std::string turtle_name) const
	{
		return peekTurtle(_turtles, turtle_name)->getName();
	}

	float Window::t_heading(std::string turtle_name) const
	{
		return peekTurtle(_turtles, turtle_name)->heading(); //Because this method throws if turtle is not found, we can assume that when returns it returns a valid pointer
	}

	Point2D Window::t_getPos(std::string turtle_name) const
	{
		return peekTurtle(_turtles, turtle_name)->getPos();
	}

	float Window::t_getPosX(std::string turtle_name) const
	{
		return t_getPos(turtle_name).x;
	}

	float Window::t_getPosY(std::string turtle_name) const
	{
		return t_getPos(turtle_name).y;
	}

	Point2D Window::t_forward(std::string turtle_name, float dist)
	{
		return findTurtle(_turtles, turtle_name)->forward(dist);
	}

	Point2D Window::t_back(std::string turtle_name, float dist)
	{
		return findTurtle(_turtles, turtle_name)->back(dist);
	}

	float Window::t_left(std::string turtle_name, float angle)
	{
		Angle a(0, angle, _angleConversionType);
		return findTurtle(_turtles, turtle_name)->left(a.delta);
	}

	float Window::t_right(std::string turtle_name, float angle)
	{
		Angle a(0, angle, _angleConversionType);
		return findTurtle(_turtles, turtle_name)->right(a.delta);
	}

	Point2D Window::t_setPos(std::string turtle_name, float x, float y)
	{
		return findTurtle(_turtles, turtle_name)->setPos(x,y);
	}

	Point2D Window::t_setPos(std::string turtle_name, Point2D p)
	{
		return findTurtle(_turtles, turtle_name)->setPos(p);
	}

	float Window::t_setHeading(std::string turtle_name, float angle)
	{
		Angle a(0, angle, _angleConversionType);
		return findTurtle(_turtles, turtle_name)->setHeading(a.delta);
	}

	RGBColor Window::t_setDrawingColor(std::string turtle_name, RGBColor color)
	{
		return findTurtle(_turtles, turtle_name)->setDrawingColor(color);
	}

	RGBColor Window::t_setDrawingColor(std::string turtle_name, int r, int g, int b, int a)
	{
		return t_setDrawingColor(turtle_name, RGBColor(r, g, b, a));
	}

	float Window::t_setDrawingThickness(std::string turtle_name, float thickness)
	{
		return findTurtle(_turtles, turtle_name)->setDrawingThickness(thickness);
	}

	PaintBrush Window::t_setPen(std::string turtle_name, PaintBrush pen)
	{
		return findTurtle(_turtles, turtle_name)->setPen(pen);
	}

	PaintBrush Window::t_setPen(std::string turtle_name, RGBColor color)
	{
		return t_setPen(turtle_name, color, _drawingBrush.thickness);
	}

	PaintBrush Window::t_setPen(std::string turtle_name, RGBColor color, float thickness)
	{
		return t_setPen(turtle_name, PaintBrush(color, thickness));
	}

	Point2D Window::t_home(std::string turtle_name)
	{
		return findTurtle(_turtles, turtle_name)->setPos(TURTLE_HOME);
	}

	void Window::t_show(std::string turtle_name)
	{
		findTurtle(_turtles, turtle_name)->show();
	}

	void Window::t_hide(std::string turtle_name)
	{
		findTurtle(_turtles, turtle_name)->hide();
	}

	void Window::t_penUp(std::string turtle_name)
	{
		findTurtle(_turtles, turtle_name)->penUp();
	}

	void Window::t_penDown(std::string turtle_name)
	{
		findTurtle(_turtles, turtle_name)->penDown();
	}

	void Window::t_swapPen(std::string turtle_name)
	{
		findTurtle(_turtles, turtle_name)->swapPen();
	}

	void Window::t_label(std::string turtle_name, std::string text, int flags)
	{
		findTurtle(_turtles, turtle_name)->label(text, flags);
	}

	void Window::t_label(std::string turtle_name, Font f, std::string text, int flags)
	{
		findTurtle(_turtles, turtle_name)->label(f, text, flags);
	}

	void Window::t_image(std::string turtle_name, Image i, int flags)
	{
		findTurtle(_turtles, turtle_name)->image(i, flags);
	}

	void Window::t_image(std::string turtle_name, std::string image_path, int flags)
	{
		findTurtle(_turtles, turtle_name)->image(image_path, flags);
	}

	void Window::t_changeMotion(std::string turtle_name, int turtle_motion)
	{
		findTurtle(_turtles, turtle_name)->changeMotion(turtle_motion);
	}

	void Window::t_setFont(std::string turtle_name, Font f)
	{
		findTurtle(_turtles, turtle_name)->setFont(f);
	}

	void Window::t_changeCursorColor(std::string turtle_name, RGBColor color)
	{
		findTurtle(_turtles, turtle_name)->changeCursorColor(color);
	}



	WindowEvent Window::waitWindowEvent()
	{
		return WindowEvent(waitForEvent());
	}

	WindowEvent Window::waitWindowEvent(WindowEventType ev_type)
	{
		return WindowEvent(waitForEvent(ev_type));
	}

	WindowEvent Window::waitWindowEventTimed(float seconds)
	{
		return WindowEvent(waitForEventTimed(seconds));
	}

	WindowEvent Window::waitWindowEventTimed(WindowEventType ev_type, float seconds)
	{
		return WindowEvent(waitForEventTimed(ev_type,seconds));
	}



	void Window::setWindowTitle(std::string title)
	{
		_windowTitle = title;
		al_set_window_title(_display, title.c_str());
	}

	ALLEGRO_TRANSFORM Window::getDefaultTransform()
	{
		ALLEGRO_TRANSFORM T;
		al_identity_transform(&T);			  //base transform, if applied now this transform doesn't change the state of the display
		al_translate_transform(&T, 0, _maxY); //move origin from top left to bottom left of the display (from old axis)
		T.m[1][1] = -1;						  //Actual Y is previous -Y
		return T;
	}

	void Window::transformCoordinates(const ALLEGRO_TRANSFORM & t, float & x, float & y)
	{
		al_transform_coordinates(&t, &x, &y);
	}

	void Window::log(Drawable * operation)
	{
		if (_drawLog.size() >= _maxLogSize) {
			delete _drawLog.front();		//remove oldest log					
			_drawLog.pop_front();									
		}
		_drawLog.push_back(operation);		//store new log
	}

	void Window::redraw()
	{
		if (_drawLogging) {

			_drawLogging = false;						//to avoid logging the redrawn primitives
			bool autoUpdate = _autoUpdate;
			disableAutoUpdate();

			for (size_t i = 0; i<_drawLog.size(); i++)	//iterate over draw log
				_drawLog[i]->draw(*this);				//draw Drawable object on actual Window 

			_drawLogging = true;						//reactivate logging draw calls
			_autoUpdate = autoUpdate;
			update();
		}
	}

	bool Window::addTurtleP(std::string turtle_name, PaintBrush pen, Point2D start_point, Font & font)
	{
		if (turtle_name == "") throw TurtleException("A turtle must have a non empty string as a name");

		Turtle t(turtle_name, this, start_point, pen, font);
		std::pair<TurtleMap::iterator, bool> insert = _turtles.insert(TurtleMapElement(t.getName(), t));
		return insert.second;
	}

	Turtle * Window::findTurtle(TurtleMap & turtle_map, MapKey turtle_name)
	{
		TurtleMap::iterator it = turtle_map.find(turtle_name);
		if (it != turtle_map.end()) {
			return &it->second;
		}
		else throw TurtleException("the turtle with name \"" + turtle_name + "\" doesn't exist");
	}

	const Turtle * Window::peekTurtle(const TurtleMap & turtle_map, MapKey turtle_name)
	{
		TurtleMap::const_iterator it = turtle_map.find(turtle_name);
		if (it != turtle_map.end()) {
			return &it->second;
		}
		else throw TurtleException("the turtle with name \"" + turtle_name + "\" doesn't exist");
	}

	Font* Window::findFont(FontMap & font_map, MapKey font_name)
	{
		FontMap::iterator it = font_map.find(font_name);
		if (it != font_map.end()) {
			return &it->second;
		}
		else throw WindowException("the font with name \"" + font_name + "\" doesn't exist");
	}

	void Window::drawTurtleCursors()
	{
		bool drawLogging = _drawLogging;
		bool autoUpdate = _autoUpdate;
		disableLogging();
		disableAutoUpdate();

		for (TurtleMap::iterator it = _turtles.begin(); it != _turtles.end(); it++) if (it->second.isVisible()) it->second.drawCursor();

		_drawLogging = drawLogging;
		_autoUpdate = autoUpdate;
	}

	bool Window::i_rotated_image(Image image, float cx, float cy, float dx, float dy, float angle, int flags)
	{
		if (image.isInvalid()) return false;

		float transformed_dx = dx, transformed_dy = dy;
		bool correct_coordinates = false;

		transformCoordinates(&_transform, &transformed_dx, &transformed_dy, correct_coordinates);

		checkActiveDisplay();

		al_draw_rotated_bitmap(image.image, cx, cy, transformed_dx, transformed_dy, -angle, flags);

		autoUpdate();

		if (_drawLogging) log(new DrawRotatedImage(image, cx, cy, dx, dy, angle, flags));

		return true;
	}



	float* Window::pointArrayToFloatArray(const Point2D * p_array, int p_length)
	{
		float* f_array;
		f_array = new float[2 * p_length];

		for (int i = 0; i < p_length; i++) {
			f_array[2 * i] = p_array[i].x;
			f_array[2 * i + 1] = p_array[i].y;
		}

		return f_array;
	}

	float Window::correctCoordinates(float x)
	{
		return x+CORRECTION_FACTOR;
	}

	void Window::transformCoordinates(const ALLEGRO_TRANSFORM * t, float * x, float * y, bool correct_coordinates)
	{
		if (correct_coordinates) {
			*x = correctCoordinates(*x);
			*y = correctCoordinates(*y);
		}
		al_transform_coordinates(t, x, y);
	}

	float* Window::getTransformedPoints(const ALLEGRO_TRANSFORM & t, const float * points, size_t n_points, bool correct_coordinates)
	{
		float * transformed_points = new float[n_points];

		for (size_t i = 0; i < n_points; i += 2) {
			transformed_points[i] = points[i];
			transformed_points[i + 1] = points[i + 1];
			if(correct_coordinates) {
				transformed_points[i] = correctCoordinates(transformed_points[i]);
				transformed_points[i + 1] = correctCoordinates(transformed_points[i + 1]);
			}
			transformCoordinates(t, transformed_points[i], transformed_points[i + 1]);
		}

		return transformed_points;
	}

	void Window::autoUpdate()
	{
		if (_autoUpdate) update();
	}

	void Window::autoRefresh()
	{
		if (_autoRefresh) {
			update();
		}
	}

	ALLEGRO_EVENT Window::waitForEvent()
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(_eventQueue, &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_SWITCH_IN) autoRefresh();
		/*else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			destroy();
			exit(-1);
		}*/

		return ev;
	}

	ALLEGRO_EVENT Window::waitForEvent(ALLEGRO_EVENT_TYPE ev_type)
	{
		ALLEGRO_EVENT ev;

		do {
			al_wait_for_event(_eventQueue, &ev);
			if (ev.type == ALLEGRO_EVENT_DISPLAY_SWITCH_IN) {
				_switchedIn = true;
				autoRefresh();
			}
			else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE && ev.type != ev_type) {
				destroy();
				exit(-1);
			}
		} while (ev.type != ev_type);

		return ev;
	}

	ALLEGRO_EVENT Window::waitForEventTimed(float seconds)
	{
		ALLEGRO_TIMER* t;
		ALLEGRO_EVENT ev;
		
		t = al_create_timer(seconds);
		if (!t) throw AllegroException("Unknown error while creating a timer in function Window::waitForEventTimed()");

		ALLEGRO_EVENT_SOURCE* t_source = al_get_timer_event_source(t);

		al_register_event_source(_eventQueue, t_source);
		al_start_timer(t);

		ev = waitForEvent();
		
		al_unregister_event_source(_eventQueue, t_source);
		al_destroy_timer(t);

		return ev;
	}

	ALLEGRO_EVENT Window::waitForEventTimed(ALLEGRO_EVENT_TYPE ev_type, float seconds)
	{
		ALLEGRO_TIMER* t;
		ALLEGRO_EVENT ev;

		t = al_create_timer(seconds);
		if (!t) throw AllegroException("Unknown error while creating a timer in function Window::waitForEventTimed()");

		ALLEGRO_EVENT_SOURCE* t_source = al_get_timer_event_source(t);

		al_register_event_source(_eventQueue, t_source);
		al_start_timer(t);

		do {
			ev = waitForEvent();
			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE && ev.type != ev_type) break;
		} while (ev.any.source != t_source && ev.type != ev_type);

		al_unregister_event_source(_eventQueue, t_source);
		al_destroy_timer(t);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE && ev.type != ev_type) {
			destroy();
			exit(-1);
		}

		return ev;
	}
	
	Point2D Window::waitMouseLeftClick(bool on_release)
	{
		return waitMouseClick(1, on_release);
	}

	Point2D Window::waitMouseRightClick(bool on_release)
	{
		return waitMouseClick(2, on_release);
	}

	Point2D Window::waitMouseAnyClick(bool on_release)
	{
		return waitMouseClick(0, on_release);
	}

	Point2D Window::waitMouseClick(unsigned int mouse_button, bool on_release)
	{
		if (!al_is_mouse_installed()) throw AllegroException("Mouse driver couldn't be loaded");

		ALLEGRO_EVENT ev;

		ALLEGRO_EVENT_TYPE target_event_type = (on_release) ? ALLEGRO_EVENT_MOUSE_BUTTON_UP : ALLEGRO_EVENT_MOUSE_BUTTON_DOWN;

		do {
			ev = waitForEvent(target_event_type);
		} while ( not(mouse_button == 0 || ev.mouse.button == mouse_button) );

		float x=ev.mouse.x, y=ev.mouse.y;

		ALLEGRO_TRANSFORM t;
		al_copy_transform(&t, &_transform);
		al_invert_transform(&t);
		transformCoordinates(t, x, y);

		return Point2D(x,y);
	}

	int Window::waitAnyKeypress(bool on_release)
	{
		return waitKeypress(ALLEGRO_KEY_MAX, on_release);
	}

	int Window::waitKeypress(int key, bool on_release)
	{
		if (!al_is_keyboard_installed()) throw AllegroException("Keyboard driver couldn't be loaded");
		
		ALLEGRO_EVENT ev;

		ALLEGRO_EVENT_TYPE target_event_type = (on_release) ? ALLEGRO_EVENT_KEY_UP : ALLEGRO_EVENT_KEY_DOWN;

		do {
			ev = waitForEvent(target_event_type);
		} while ( not(key == ALLEGRO_KEY_MAX || ev.keyboard.keycode == key) );

		return ev.keyboard.keycode;
	}

	void Window::waitWindowCloseButton()
	{
		waitForEvent(ALLEGRO_EVENT_DISPLAY_CLOSE);
	}

	ALLEGRO_DISPLAY* Window::getDisplay()
	{
		return _display;
	}

	WindowSpec Window::getWindowSpec() const
	{
		return WindowSpec(al_get_display_width(_display), al_get_display_height(_display));
	}

	int Window::getWindowX() const
	{
		return al_get_display_width(_display);
	}

	int Window::getWindowY() const
	{
		return al_get_display_height(_display);
	}

	void Window::turtleMoved()
	{
		_turtleCursorMoved = true;
	}

	void Window::turtleLine(Point2D p1, Point2D p2, RGBColor color, float thickness, bool showing_cursor)
	{
		bool drawLogging = _drawLogging;
		disableLogging();

		line(p1, p2, color, thickness);

		_drawLogging = drawLogging;
		
		if (_drawLogging) log(new DrawTurtleLine(p1,p2,color,thickness, showing_cursor));
	}

	bool Window::turtle_rotated_image(Image image, Point2D c, Point2D d, float angle, int flags)
	{
		return i_rotated_image(image, c.x, c.y, d.x, d.y, angle, flags);
	}

	void Window::cursorUpdate()
	{
		autoUpdate();
	}

	void Window::init(std::string window_title, int width, int height, RGBColor backgroundColor, RGBColor drawingColor, double lineWidth, bool inRadians, size_t logSize)
	{
		if (!al_init()) throw AllegroException("Error initializing Allegro"); //initializing Allegro

		_display = al_create_display(width, height);

		if (!_display) throw AllegroException("Error while creating Display"); //initializing display

		if (!al_init_image_addon()) throw AllegroException("Error loading Allegro image addon");

		if (!al_init_font_addon()) throw AllegroException("Error initializing Allegro font addon");

		if (!al_init_ttf_addon()) throw AllegroException("Error loading TrueType Font addon");

		if (!al_init_primitives_addon()) throw AllegroException("Error initializing Allegro primitves addon");

		eventInit();

		setWindowTitle(_windowTitle);

		_minX = _minY = 0;
		_maxX = width;
		_maxY = height;

		_autoUpdate = true;
		_drawLogging = false;
		_autoRefresh = false;
		_turtleCursorMoved = false;
		_switchedIn = false;

		changeBackgroundColor(backgroundColor);
		_drawingBrush = PaintBrush(drawingColor, lineWidth);

		_transform = getDefaultTransform();

		_angleConversionType = (inRadians) ? NO_CONVERSION : DEGS_TO_RADS;

		_maxLogSize = logSize;

		addFont(DEFAULT_FONT_NAME, DEFAULT_FONT_PATH);
		setActiveFont(DEFAULT_FONT_NAME);
		_defaultFont = &_fonts.find(DEFAULT_FONT_NAME)->second;
		_activeFont = _defaultFont;

		addTurtle(DEFAULT_TURTLE_NAME);
		setActiveTurtle(DEFAULT_TURTLE_NAME);

		NUMBER_OF_DISPLAYS++;
	}

	void Window::eventInit()
	{
		_eventQueue = al_create_event_queue();
		if (!_eventQueue) throw AllegroException("Error creating an Allegro event queue for class Window");
		al_install_mouse();
		al_install_keyboard();

		al_register_event_source(_eventQueue, al_get_display_event_source(_display));
		al_register_event_source(_eventQueue, al_get_mouse_event_source());
		al_register_event_source(_eventQueue, al_get_keyboard_event_source());
	}

	void Window::destroy()
	{
		clearDrawLog();
		_turtles.clear();
		_fonts.clear();
		al_destroy_event_queue(_eventQueue);
		//al_set_target_bitmap(NULL);
		al_destroy_display(_display);
		if (NUMBER_OF_DISPLAYS == 1) { //if its the last display to be destroyed
			al_uninstall_mouse();
			al_uninstall_keyboard();
			al_shutdown_ttf_addon();
			al_shutdown_font_addon();
			al_shutdown_image_addon();
			al_shutdown_primitives_addon();
			//al_uninstall_system();
		}
		NUMBER_OF_DISPLAYS--;
		//delete _activeTurtle; don't do this, it's a bad idea
	}

	void Window::copy(const Window & w)
	{
		_display = al_create_display(w._maxX, w._maxY);

		if (!_display) throw AllegroException("Error while creating Display"); //initializing display

		eventInit();

		setWindowTitle(w._windowTitle);

		_minX = w._minX;
		_minY = w._minY;
		_maxX = w._maxX;
		_maxY = w._maxY;

		_angleConversionType = w._angleConversionType;

		changeBackgroundColor(w._backgroundColor);
		_drawingBrush = w._drawingBrush;
		_transform = w._transform;

		_drawLog = w._drawLog;
		_maxLogSize = w._maxLogSize;

		_turtles = w._turtles;
		_activeTurtle = findTurtle(_turtles, DEFAULT_TURTLE_NAME);
		
		_fonts = w._fonts;
		setActiveFont(DEFAULT_FONT_NAME);
		_defaultFont = findFont(_fonts, DEFAULT_FONT_NAME);
		
		_autoUpdate = w._autoUpdate;
		_drawLogging = w._drawLogging;
		_autoRefresh = w._autoRefresh;
		_turtleCursorMoved = w._turtleCursorMoved;
		_switchedIn = w._switchedIn;

		NUMBER_OF_DISPLAYS++;
	}

	void Window::checkActiveDisplay()
	{
		ALLEGRO_BITMAP * my_backbuffer = al_get_backbuffer(_display);
		if (al_get_target_bitmap() != my_backbuffer) {
			al_set_target_bitmap(my_backbuffer);
		}
	}

	void Window::clearDrawLog()
	{
		for (size_t i = 0; i < _drawLog.size(); i++) delete _drawLog[i];
		_drawLog.clear();
	}


	/*
	void Window::setupDisplay()
	{
		ALLEGRO_TRANSFORM T;
		
		al_identity_transform(&T); //base transform, if applied now this transform doesn't change the state of the display
		al_rotate_transform_3d(&T, 1, 0, 0, ALLEGRO_PI); //3D rotation of 180 degrees along X axis (1,0,0 vector). Actual Y is previous -Y
		al_translate_transform(&T, 0, _maxY); //move origin from top left to bottom left of the display (from old axis)
		

		//alternative version
		al_identity_transform(&T);			  //base transform, if applied now this transform doesn't change the state of the display
		al_translate_transform(&T, 0, _maxY); //move origin from top left to bottom left of the display (from old axis)
		T.m[1][1] = -1;						  //Actual Y is previous -Y

		al_use_transform(&T);				  //apply transform to the display
	}*/
