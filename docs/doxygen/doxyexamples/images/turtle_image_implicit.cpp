int main(int argc, char **argv){
    Window w(300,300);

    w.t_setPos(50, 50);

    w.t_image("city.png");

    w.waitWindowCloseButton();

    return 0;
}