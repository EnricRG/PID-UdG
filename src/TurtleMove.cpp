#include "TurtleMove.h"

TurtleMove::single_move_const_iterator::single_move_const_iterator()
{
}

TurtleMove::single_move_const_iterator::single_move_const_iterator(TurtleMove move)
{
	_move = move;
}

TurtleMove::single_move_const_iterator::~single_move_const_iterator()
{
}

bool TurtleMove::single_move_const_iterator::hasNext() const
{
	return false;
}

const TurtleMove TurtleMove::single_move_const_iterator::next()
{
	return _move;
}

const TurtleMove TurtleMove::single_move_const_iterator::actual()
{
	return _move;
}

TurtleMove::multiple_move_const_iterator::multiple_move_const_iterator()
{
	init(std::vector<TurtleMove>(0));
}

TurtleMove::multiple_move_const_iterator::multiple_move_const_iterator(const std::vector<TurtleMove>& v)
{
	init(v);
}

TurtleMove::multiple_move_const_iterator::~multiple_move_const_iterator()
{
}

bool TurtleMove::multiple_move_const_iterator::hasNext() const
{
	return _position < _moves.size() - 1;
}

const TurtleMove TurtleMove::multiple_move_const_iterator::next()
{
	if (hasNext()) _position++;
	return actual();
}

const TurtleMove TurtleMove::multiple_move_const_iterator::actual()
{
	return _moves[_position];
}

void TurtleMove::multiple_move_const_iterator::init(const std::vector<TurtleMove>& v)
{
	_moves = v;
	_position = 0;
}

TurtleMove::TurtleMove()
{
	visibleMove = false;
}

TurtleMove::TurtleMove(Point2D p, bool isVisible)
{
	init(p, isVisible);
}

TurtleMove::~TurtleMove()
{
}

Point2D TurtleMove::getDestination() const
{
	return destination;
}

bool TurtleMove::isVisible() const
{
	return visibleMove;
}

void TurtleMove::init(Point2D p, bool isVisible)
{
	destination = p;
	visibleMove = isVisible;
}
