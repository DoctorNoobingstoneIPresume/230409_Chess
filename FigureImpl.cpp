#include "FigureImpl.hpp"

namespace Chess1
{

FigureImpl::~FigureImpl
()
{}

bool
FigureImpl::CanTravelBackAndForth
()
const
{
	return Do_CanTravelBackAndForth ();
}

bool
FigureImpl::CanMove
(const Board &board, const Position &position0, const Position &position1)
const
{
	Azzert (position1 != position0);
	//Azzert (board.at (position1).empty ());
	const bool bResult_Forth = Do_CanMove (board, position0, position1);
	
	if (Do_CanTravelBackAndForth ())
	{
		const bool bResult_Back = Do_CanMove (board, position1, position0);
		Azzert (bResult_Back == bResult_Forth);
	}
	
	return bResult_Forth;
}

bool
FigureImpl::CanAttack
(const Board &board, const Position &position0, const Position &position1)
const
{
	return false; // [2023-04-11] TODO !!
}

}
