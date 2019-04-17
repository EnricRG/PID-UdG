#include "windowAddon/WindowAddon.h"

int main(){
	Window w(300,300);

	w.circle(150,150,50);
	w.rest(0.5);
	//w.t_show();
	//w.t_forward(50);

	//w.waitAnyKeypress();
	w.text(150,150,"It's Working", TEXT_ALIGN_CENTER);

	w.waitAnyKeypress();

	return 0;
}
