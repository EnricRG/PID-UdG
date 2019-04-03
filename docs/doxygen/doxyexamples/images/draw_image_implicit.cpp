int main(int argc, char **argv){
    Window w(300,300);

    w.image("city.png", 50, 50);

    w.waitWindowCloseButton();

    return 0;
}