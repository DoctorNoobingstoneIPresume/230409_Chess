#pragma once

#include "Position.hpp"

#include <boost/core/noncopyable.hpp>

#include <string>
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
	std::string
	Do_GetTypeID
	()
	const
	= 0;
	
	virtual
	std::istream &
	Do_Get
	(std::istream &is);
	
	// [2023-05-14 :x]
	//virtual
	//bool
	//Do_CanTravelBackAndForth
	//()
	//const
	//= 0;
	//
	//virtual
	//bool
	//Do_CanMove
	//(const Board &board, const Position &position0, const Position &position1)
	//const
	//= 0;
	//
	//virtual
	//bool
	//Do_CanAttack
	//(const Board &board, const Position &position0, const Position &position1)
	//const
	//= 0;

 public:
	std::string
	GetTypeID
	()
	const;
	
	std::ostream &
	Put
	(std::ostream &os)
	const;
	
	std::istream &
	Get
	(std::istream &is);
	
	// [2023-05-14 :x]
	//bool
	//CanTravelBackAndForth
	//()
	//const;
	//
	//bool
	//CanMove
	//(const Board &board, const Position &position0, const Position &position1)
	//const;
	//
	//bool
	//CanAttack
	//(const Board &board, const Position &position0, const Position &position1)
	//const;
};

std::ostream &operator<< (std::ostream &os, const FigureImpl &figureimpl);

}
