#pragma once

#include "_Fwd.hpp"

#include <iosfwd>

namespace Chess1
{

class Position
{
 private:
	      Coord                  _x;
	      Coord                  _y;

 public:
	Coord GetX () const;
	Coord GetY () const;
	
	Position &SetX (Coord value);
	Position &SetY (Coord value);
	
	explicit Position (Coord x = -1, Coord y = -1);
	
	std::ostream &Put (std::ostream &os) const;
	std::istream &Get (std::istream &is);
};

std::ostream &operator<< (std::ostream &os, const Position &object);
std::istream &operator>> (std::istream &is,       Position &object);

bool operator== (const Position &object0, const Position &object1);
bool operator!= (const Position &object0, const Position &object1);

}
