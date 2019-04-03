int main(int argc, char **argv){
    Window w(200,200);

    w.t_penUp(); //In this case we don't want the Turtle to paint its path.

    w.t_setPos(100,100); //Put the turtle at the center of the screen.
    w.pixel(100,100); //Lit the pixel where the turtle has landed the first time. Only for representation purposes.

    //do stuff

    w.t_left(90);   //Set Turtle direction relatively, 90 degrees left.
    w.t_forward(50);

    w.t_label("Your text goes here", TEXT_ALIGN_CENTER);

    // do more stuff

    w.waitWindowCloseButton();

    return 0;
}