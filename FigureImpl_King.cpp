#include "FigureImpl_King.hpp"
#include "FigureImplUtil.hpp"
#include "Board.hpp"

namespace Chess1
{

FigureImpl_King::FigureImpl_King
():
	_nTeleports (2)
{}

FigureImpl *
FigureImpl_King::Do_Clone
()
const
{
	return new FigureImpl_King (*this);
}

std::string
FigureImpl_King::Do_GetTypeID
()
const
{
	return "king";
}

std::istream &
FigureImpl_King::Do_Get
(std::istream &is)
{
	is >> _nTeleports;
	return is;
}

bool
FigureImpl_King::Do_CanMove
(const Board &board, const Position &pos0, const Position &pos1)
const
{
	const Coord dx = Coord_AbsDiff (pos0.GetX (), pos1.GetX ());
	const Coord dy = Coord_AbsDiff (pos0.GetY (), pos1.GetY ());
	if (dx <= 1 && dy <= 1)
		return true;
	
	if (_nTeleports && ! board.At (pos1).IsOccupied ())
		return true;
}

void
FigureImpl_King::Do_BeforeMove
(const Board &board, const Position &pos0, const Position &pos1)
{
	const Coord dx = Coord_AbsDiff (pos0.GetX (), pos1.GetX ());
	const Coord dy = Coord_AbsDiff (pos0.GetY (), pos1.GetY ());
	if (dx <= 1 && dy <= 1)
		return;
	
	Azzert (_nTeleports && ! board.At (pos1).IsOccupied ());
	--_nTeleports;
}

}
