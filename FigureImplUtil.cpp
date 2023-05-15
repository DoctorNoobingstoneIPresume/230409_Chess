#include "FigureImplUtil.hpp"
#include "Board.hpp"
#include "Position.hpp"

namespace Chess1
{

Coord Coord_AbsDiff (Coord a, Coord b)
{
	return a >= b ? a - b : b - a;
}

bool IsStraightLine (const Board &board, const Position &pos0, const Position &pos1)
{
	const Coord
		x0 = pos0.GetX (),
		y0 = pos0.GetY (),
		x1 = pos1.GetX (),
		y1 = pos1.GetY ();
	
	Coord stepx;
	Coord stepy;
	{
		if (x1 == x0)
		{
			stepx = 0;
			stepy = y0 < y1 ? 1 : -1;
		}
		else
		if (y1 == y0)
		{
			stepx = x0 < x1 ? 1 : -1;
			stepy = 0;
		}
		else
			return false;
	}
	
	for (Coord x = x0 + stepx, y = y0 + stepy; x != x1 || y != y1; x += stepx, y += stepy)
		if (board.At (Position (x, y)).IsOccupied ())
			return false;
	
	return true;
}

bool IsDiagonalLine (const Board &board, const Position &pos0, const Position &pos1)
{
	const Coord
		x0 = pos0.GetX (),
		y0 = pos0.GetY (),
		x1 = pos1.GetX (),
		y1 = pos1.GetY (),
		dx = Coord_AbsDiff (x0, x1),
		dy = Coord_AbsDiff (y0, y1);
	
	Coord stepx;
	Coord stepy;
	{
		if (dx == dy)
		{
			stepx = x0 < x1 ? 1 : -1;
			stepy = y0 < y1 ? 1 : -1;
		}
		else
			return false;
	}
	
	for (Coord x = x0 + stepx, y = y0 + stepy; x != x1 || y != y1; x += stepx, y += stepy)
		if (board.At (Position (x, y)).IsOccupied ())
			return false;
	
	return true;
}

}
