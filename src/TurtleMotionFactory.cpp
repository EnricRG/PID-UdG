#include "TurtleMotionFactory.h"
#include "WindowTurtleMotion.h"
#include "FenceTurtleMotion.h"
#include "WrapTurtleMotion.h"


TurtleMotionFactory::TurtleMotionFactory()
{
}


TurtleMotionFactory::~TurtleMotionFactory()
{
}

TurtleMotion * TurtleMotionFactory::makeTurtleMotion(int motion_type)
{
	TurtleMotion * motion;

	switch (motion_type) {
/*		case WRAP_MODE:
			motion = new WrapTurtleMotion();
			break;*/
		case WINDOW_MODE:
			motion = new WindowTurtleMotion();
			break;
		case FENCE_MODE:
			motion = new FenceTurtleMotion();
			break;
		default: 
			motion = 0; //NULL
	}

	return motion;
}
