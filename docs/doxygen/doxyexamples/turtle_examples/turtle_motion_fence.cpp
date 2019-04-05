const int WIDTH = 201;

int main(int argc, char **argv) {
	Window w(WIDTH, WIDTH); //White background color and black drawing color by default.
	
	w.t_setPos(WIDTH/2, WIDTH/2); //move to the center of the screen.
	
	w.t_show(); //make turtle visible.

	w.t_changeMotion(FENCE_MODE);

	w.t_forward(WIDTH);

	w.waitWindowCloseButton();

	return 0;
}