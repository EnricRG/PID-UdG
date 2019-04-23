#include "WindowAddon.h"

int main(int argc, char **argv) {
	Window w(201, 201);

	Point2D points[7];
	points[0] = Point2D(90, 80);    //filled polygon, bottom left corner
	points[1] = Point2D(110, 80);   //filled polygon, bottom right corner
	points[2] = Point2D(120, 130);  //filled polygon, top right corner
	points[3] = Point2D(80, 130);   //filled polygon, top left corner
	points[4] = Point2D(95, 95);    //hole, bottom left corner
	points[5] = Point2D(101, 110);  //hole, top corner
	points[6] = Point2D(107, 95);   //hole, bottom right corner

	int vertex_counts[] = {
       4, // number of vertices for filled polygon
       3, // number of vertices for hole
       0  // terminator
    };

	w.filled_polygon_with_holes(points, vertex_counts); //Using w drawing parameters (in this case, black drawing color)

	w.waitWindowCloseButton();
	
	return 0;
}