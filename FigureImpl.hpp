#pragma once

#include "Position.hpp"

#include <boost/core/noncopyable.hpp>

#include <iosfwd>

namespace Chess1
{

class Board;

class FigureImpl:
	boost::noncopyable
{
 public:
	virtual
	~FigureImpl
	();

 private:
	virtual
	bool
	Do_CanTravelBackAndForth
	()
	const
	= 0;
	
	virtual
	bool
	Do_CanMove
	(const Board &board, const Position &position0, const Position &position1)
	const
	= 0;
	
	virtual
	bool
	Do_CanAttack
	(const Board &board, const Position &position0, const Position &position1)
	const
	= 0;

 public:
	bool
	CanTravelBackAndForth
	()
	const;
	
	bool
	CanMove
	(const Board &board, const Position &position0, const Position &position1)
	const;
	
	bool
	CanAttack
	(const Board &board, const Position &position0, const Position &position1)
	const;
};

}
