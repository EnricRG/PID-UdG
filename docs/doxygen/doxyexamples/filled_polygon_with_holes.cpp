float vertices[] = {
	  0,   0, // filled polygon, upper left corner
	  0, 100, // filled polygon, lower left corner
	100, 100, // filled polygon, lower right corner
	100,   0, // filled polygon, upper right corner
	 10,  10, // hole, upper left
	 90,  10, // hole, upper right
	 90,  90  // hole, lower right
};

int vertex_counts[] = {
   4, // number of vertices for filled polygon
   3, // number of vertices for hole
   0  // terminator
};