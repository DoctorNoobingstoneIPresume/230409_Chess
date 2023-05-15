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
	
	virtual
	bool
	Do_CanTravelBackAndForth
	()
	const;
	
	virtual
	bool
	Do_CanMove
	(const Board &board, const Position &pos0, const Position &pos1)
	const
	= 0;

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
	
	bool
	CanTravelBackAndForth
	()
	const;
	
	bool
	CanMove
	(const Board &board, const Position &pos0, const Position &pos1)
	const;
};

std::ostream &operator<< (std::ostream &os, const FigureImpl &figureimpl);

}
