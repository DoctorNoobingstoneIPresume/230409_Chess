#include "FigureImpl_Pawn.hpp"
#include "Board.hpp"
#include "Cell.hpp"

namespace Chess1
{

FigureImpl *
FigureImpl_Pawn::Do_Clone
()
const
{
	return new FigureImpl_Pawn (*this);
}

std::string
FigureImpl_Pawn::Do_GetTypeID
()
const
{
	return "pawn";
}

bool
FigureImpl_Pawn::Do_CanTravelBackAndForth
()
const
{
	return false;
}

bool
FigureImpl_Pawn::Do_CanMove
(const Board &board, const Position &pos0, const Position &pos1)
const
{
	const Cell &cell0 = board.At (pos0);
	const Cell &cell1 = board.At (pos1);
	
	const unsigned iPlayer0 = cell0.GetPlayer ();
	const unsigned iPlayer1 = cell1.GetPlayer ();
	
	const Coord
		x0 = pos0.GetX (),
		x1 = pos1.GetX (),
		y0 = pos0.GetY (),
		y1 = pos1.GetY ();
	
	if (IsValidPlayer (iPlayer1))
	{
		if (x1 != x0 - 1 && x1 != x0 + 1)
			return false;
	}
	
	if (! iPlayer0)
	{
		if (IsValidPlayer (iPlayer1))
		{
			if (y1 != y0 + 1)
				return false;
		}
		else
		{
			if (y0 <= 1)
				{ if (y1 < y0 + 1 || y1 > y0 + 2) return false; }
			else
				{ if (y1 != y0 + 1) return false; }
		}
		
	}
	else
	if (iPlayer0 == 1)
	{
		if (IsValidPlayer (iPlayer1))
		{
			if (y1 != y0 - 1)
				return false;
		}
		else
		{
			if (y0 >= g_cyBoard - 2)
				{ if (y1 < y0 - 2 || y1 > y0 - 1) return false; }
			else
				{ if (y1 != y0 - 1) return false; }
		}
	}
	else
		Azzert (0);
	
	return true;
	
}

}
