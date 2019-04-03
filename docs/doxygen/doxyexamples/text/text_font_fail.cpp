int main(int argc, char **argv){
    Window w(200,200);

    Font f("Fonts/open-sans/OpenSans-Bold.ttf", WHITE, 16); //Setting up the font, with white color and size 16.

    w.text(f, 100,100, "Your text goes here", TEXT_ALIGN_CENTER);

    w.waitWindowCloseButton();

    return 0;
}