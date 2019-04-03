int main(int argc, char **argv){
    Window w(300,300);

    Image i("city.png");

    w.t_setPos(50, 50);

    w.t_image(i);

    w.waitWindowCloseButton();

    return 0;
}