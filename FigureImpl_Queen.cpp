#include "FigureImpl_Queen.hpp"
#include "FigureImplUtil.hpp"

namespace Chess1
{

FigureImpl *
FigureImpl_Queen::Do_Clone
()
const
{
	return new FigureImpl_Queen (*this);
}


std::string
FigureImpl_Queen::Do_GetTypeID
()
const
{
	return "queen";
}

bool
FigureImpl_Queen::Do_CanMove
(const Board &board, const Position &pos0, const Position &pos1)
const
{
	return IsStraightLine (board, pos0, pos1) || IsDiagonalLine (board, pos0, pos1);
}

}
