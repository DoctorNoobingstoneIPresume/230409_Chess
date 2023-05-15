#include "FigureImpl_Knight.hpp"
#include "FigureImplUtil.hpp"

namespace Chess1
{

FigureImpl *
FigureImpl_Knight::Do_Clone
()
const
{
	return new FigureImpl_Knight (*this);
}

std::string
FigureImpl_Knight::Do_GetTypeID
()
const
{
	return "knight";
}

bool
FigureImpl_Knight::Do_CanMove
(const Board &board, const Position &pos0, const Position &pos1)
const
{
	const Coord
		x0 = pos0.GetX (),
		y0 = pos0.GetY (),
		x1 = pos1.GetX (),
		y1 = pos1.GetY (),
		dx = Coord_AbsDiff (x0, x1),
		dy = Coord_AbsDiff (y0, y1);
	
	return dx == 1 && dy == 2 || dx == 2 && dy == 1;
}

}
