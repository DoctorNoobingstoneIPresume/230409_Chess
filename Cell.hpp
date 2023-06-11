#pragma once

#include "_FwdConfig.hpp"
#if BUILD_SCRIPT_DEBUG
 #include "Board.hpp"
#endif
#include "_Fwd.hpp"

#include <iosfwd>
#include <memory>

namespace Chess1
{

class FigureImpl;

// For CanMove:
class Board;
class Position;

class Cell
{
 private:
	      std::unique_ptr <FigureImpl>             _pImpl;
	      unsigned                                 _iPlayer;

 public:
	~Cell
	();
	
	void
	Swap
	(Cell &rhs)
	noexcept;
	
	Cell
	(Cell &&rhs)
	noexcept;
	
	Cell &
	operator=
	(Cell &&rhs)
	noexcept;
	
	Cell
	();
	
	Cell
	(std::unique_ptr <FigureImpl>, unsigned iPlayer);

 public:
	unsigned
	GetPlayer
	()
	const;
	
	bool
	IsOccupied
	()
	const;
	
	std::string
	GetTypeID
	()
	const;
	
	bool
	CanMove
	(const Board &board, const Position &pos0, const Position &pos1)
	const;
	
	void
	BeforeMove
	(const Board &board, const Position &pos0, const Position &pos1);
	
	// [2023-05-15]
	//const FigureImpl *
	//AdrImpl
	//()
	//const;
	//
	//FigureImpl *
	//AdrImpl
	//();

 public:
	std::ostream &Put (std::ostream &os) const;
	std::istream &Get (std::istream &is);
};

std::ostream &operator<< (std::ostream &os, const Cell &cell);
std::istream &operator>> (std::istream &is,       Cell &cell);

}
