#include "Position.hpp"

#include <iostream>

namespace Chess1
{

Coord Position::GetX () const { return _x; }
Coord Position::GetY () const { return _y; }

Position &Position::SetX (Coord value) { _x = value; return *this; }
Position &Position::SetY (Coord value) { _y = value; return *this; }

Position::Position (Coord x, Coord y):
	_x (x),
	_y (y)
{
	Azzert (x >= 0 && x < g_cxBoard || x == Coord (-1)); // Azzert (x + 1 <= cxBoard);
	Azzert (y >= 0 && y < g_cyBoard || y == Coord (-1)); // Azzert (y + 1 <= cyBoard);
}

namespace
{
	const char *const names_for_x = "?ABCDEFGH";
	const char *const names_for_y = "?12345678";
}

std::ostream &Position::Put (std::ostream &os) const
{
	const char ac [3] =
	{
		names_for_x [_x + 1],
		names_for_y [_y + 1],
		0                     // Redundantly specified for (debatable) clarity.
	};
	
	return os << ac;
}

std::ostream &operator<< (std::ostream &os, const Position &object)
{
	return object.Put (os);
}

bool operator== (const Position &object0, const Position &object1)
{
	return
		object0.GetX () == object1.GetX ()
		&&
		object0.GetY () == object1.GetY ();
}

bool operator!= (const Position &object0, const Position &object1)
{
	return ! (object0 == object1);
}

}
