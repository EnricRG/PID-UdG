int main(int argc, char **argv){
    Window w(200,200);

    w.t_show(); //By default, a Turtle doesn't show its position. With this function you enable this capability. To revert it, use Window::t_hide();

    w.t_setPos(100,100);
    w.pixel(100,100); //Lit the pixel where the turtle has landed the first time. Only for representation purposes.

    //do stuff

    w.t_setHeading(90); //Set Turtle direction absolutely, pointing upwards.
    w.t_forward(50);

    // do more stuff

    w.waitWindowCloseButton();
	
	return 0;
}