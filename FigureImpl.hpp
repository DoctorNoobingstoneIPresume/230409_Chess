#pragma once

#include "Position.hpp"

// [2023-05-15] We are implementing cloning.
//include <boost/core/noncopyable.hpp>

#include <string>
#include <iosfwd>
#include <memory>

namespace Chess1
{

class Board;

class FigureImpl
{
 public:
	virtual
	~FigureImpl
	();

 protected:
	FigureImpl
	(const FigureImpl &rhs);
	
	FigureImpl
	();

 private:
	FigureImpl &
	operator=
	(const FigureImpl &rhs)
	= delete;

 private:
	virtual
	FigureImpl *
	Do_Clone
	()
	const
	= 0;
	
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
	
	virtual
	void
	Do_BeforeMove
	(const Board &board, const Position &pos0, const Position &pos1);

 public:
	std::unique_ptr <FigureImpl>
	Clone
	()
	const;
	
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
	
	void
	BeforeMove
	(const Board &board, const Position &pos0, const Position &pos1);
};

std::ostream &operator<< (std::ostream &os, const FigureImpl &figureimpl);

}
