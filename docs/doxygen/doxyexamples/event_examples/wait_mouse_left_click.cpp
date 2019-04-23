#include "WindowAddon.h"

int main(int argc, char **argv){
    Window w(300, 300);

    w.waitMouseLeftClick();

    w.text(150, 150, "Hey there!", TEXT_ALIGN_CENTER);

    w.waitWindowCloseButton();

    return 0;
}