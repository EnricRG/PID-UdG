#ifndef TURTLEMOVE_H
#define TURTLEMOVE_H

#include <vector>

#include "Point2D.h"

class TurtleMove
{
	public:
		TurtleMove();
		TurtleMove(Point2D p, bool isVisible = false);
		~TurtleMove();

		Point2D getDestination() const;
		bool isVisible() const;

		class const_iterator;
		class single_move_const_iterator;
		class multiple_move_const_iterator;

	private:
		Point2D destination;
		bool visibleMove;

		void init(Point2D p, bool isVisible);
};

class TurtleMove::const_iterator {
	public:
		virtual bool hasNext() const = 0;
		virtual const TurtleMove next() = 0;
		virtual const TurtleMove actual() = 0;
};

class TurtleMove::single_move_const_iterator : public TurtleMove::const_iterator {
	public:
		single_move_const_iterator();
		single_move_const_iterator(TurtleMove move);
		~single_move_const_iterator();

		bool hasNext() const;
		const TurtleMove next();
		const TurtleMove actual();
	private:
		TurtleMove _move;
};

class TurtleMove::multiple_move_const_iterator : public TurtleMove::const_iterator {
	public:
		multiple_move_const_iterator();
		multiple_move_const_iterator(const std::vector<TurtleMove> & v);
		~multiple_move_const_iterator();

		bool hasNext() const;
		const TurtleMove next();
		const TurtleMove actual();
	private:
		std::vector<TurtleMove> _moves;
		unsigned _position;

		void init(const std::vector<TurtleMove> & v);
};

#endif