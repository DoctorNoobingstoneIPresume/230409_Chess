#pragma once

#include "Cell.hpp"

#include <vector>
#include <iosfwd>

namespace Chess1
{

class Position;

class Board
{
 private:
	      std::vector <Cell>                _contCells;

 public:
	Board ();

 public:
	const Cell &At (const Position &pos) const;
	      Cell &At (const Position &pos);
	
	std::ostream &Put (std::ostream &os) const;
	std::istream &Get (std::istream &is);
};

std::ostream &operator<< (std::ostream &os, const Board &board);
std::istream &operator>> (std::istream &is,       Board &board);

}
