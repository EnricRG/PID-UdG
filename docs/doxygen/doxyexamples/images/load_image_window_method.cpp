int main(int argc, char **argv){
    Window w(300,300);

    Image i = w.loadImage("city.png"); //relative file path

    w.image(i, 50, 50);

    w.waitWindowCloseButton();

    return 0;
}