#include "Window.h"

int main(int argc, char **argv) {
	Window w(201, 201);

	float points[14]= {
        90, 80,    //filled polygon, bottom left corner
        110, 80,   //filled polygon, bottom right corner
        120, 130,  //filled polygon, top right corner
        80, 130,   //filled polygon, top left corner
        95, 95,    //hole, bottom left corner
        101, 110,  //hole, top corner
        107, 95    //hole, bottom right corner
    };

	int vertex_counts[] = {
       4, // number of vertices for filled polygon
       3, // number of vertices for hole
       0  // terminator
    };

	w.filled_polygon_with_holes(points, vertex_counts, BLACK);

	w.waitWindowCloseButton();
	
	return 0;
}