#ifndef TURTLEMOTION_H
#define TURTLEMOTION_H

#include "WindowSpec.h"
#include "Point2D.h"

#include "CommonUtils.h"

//static const int WRAP_MODE = 1; //When turtle runs to an edge of the screen, it appears on the opposite edge
static const int WINDOW_MODE = 2;	//When turtle runs to an edge of the screen, it continues forward outside the screen
static const int FENCE_MODE = 3;	//When turtle runs to an edge of the screen, it stops

struct Move {
	Point2D next_point;
	bool painting;
};

struct TurtleMovement {
	Move * movements;
	int n_movements;

	TurtleMovement(Move moves[], int n_moves) {
		movements = getCopyOfArray(moves, n_moves);
		n_movements = n_moves;
	}

	~TurtleMovement() {
		destroy();
	}

	void destroy() {
		delete movements;
	}
};

class TurtleMotion 
{
public:
	virtual ~TurtleMotion() {};
	virtual Point2D nextPosition(Point2D actual_position, float direction, float distance, WindowSpec window) = 0;
	virtual int type() = 0;
};

#endif