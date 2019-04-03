int main(int argc, char **argv){
    Window w(200,200);

    w.addFont("myFont","Fonts/open-sans/OpenSans-Bold.ttf", RED, 16); //Setting up and storing the font, with red color and size 16.

    w.text("myFont", 100,100, "Your text goes here", TEXT_ALIGN_CENTER);

    w.waitWindowCloseButton();

    return 0;
}