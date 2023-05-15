#include "FigureImpl_Bishop.hpp"
#include "FigureImplUtil.hpp"

namespace Chess1
{

FigureImpl *
FigureImpl_Bishop::Do_Clone
()
const
{
	return new FigureImpl_Bishop (*this);
}

std::string
FigureImpl_Bishop::Do_GetTypeID
()
const
{
	return "bishop";
}

bool
FigureImpl_Bishop::Do_CanMove
(const Board &board, const Position &pos0, const Position &pos1)
const
{
	return IsDiagonalLine (board, pos0, pos1);
}

}
