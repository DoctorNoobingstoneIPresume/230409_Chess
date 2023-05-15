#include "FigureImpl_Rook.hpp"
#include "FigureImplUtil.hpp"

namespace Chess1
{

std::string
FigureImpl_Rook::Do_GetTypeID
()
const
{
	return "rook";
}

bool
FigureImpl_Rook::Do_CanMove
(const Board &board, const Position &pos0, const Position &pos1)
const
{
	return IsStraightLine (board, pos0, pos1);
}

}
