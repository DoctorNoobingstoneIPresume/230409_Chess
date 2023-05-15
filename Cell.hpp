#pragma once

#include "_Fwd.hpp"

#include <iosfwd>
#include <memory>

namespace Chess1
{

class FigureImpl;

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

 public:
	std::ostream &Put (std::ostream &os) const;
	std::istream &Get (std::istream &is);
};

std::ostream &operator<< (std::ostream &os, const Cell &cell);
std::istream &operator>> (std::istream &is,       Cell &cell);

}