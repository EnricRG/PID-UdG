int main(int argc, char **argv){
    Window w(200,200);

    w.triangle(30, 50, 170, 50, 100, 170);
    w.circle(100, 90, 40, BLACK);
    w.line(100, 170, 100, 50);

    w.saveToFile("screenshot","png");

    w.waitWindowCloseButton();

    return 0;
}