#include "FigureImpl.hpp"
#include "Board.hpp"
#include "Cell.hpp"

#include <iostream>

namespace Chess1
{

FigureImpl::~FigureImpl
()
{}

std::istream &
FigureImpl::Do_Get
(std::istream &is)
{
	return is;
}

bool
FigureImpl::Do_CanTravelBackAndForth
()
const
{
	return true;
}

bool
FigureImpl::CanTravelBackAndForth
()
const
{
	return Do_CanTravelBackAndForth ();
}

bool
FigureImpl::CanMove
(const Board &board, const Position &pos0, const Position &pos1)
const
{
	Azzert (pos1 != pos0);
	
	const Cell &cell0 = board.At (pos0);
	const unsigned iPlayer0 = cell0.GetPlayer ();
	Azzert (IsValidPlayer (iPlayer0));
	
	const Cell &cell1 = board.At (pos1);
	const unsigned iPlayer1 = cell1.GetPlayer ();
	Azzert (iPlayer1 != iPlayer0);
	
	//Azzert (board.at (pos1).empty ());
	const bool bResult_Forth = Do_CanMove (board, pos0, pos1);
	
	if (Do_CanTravelBackAndForth ())
	{
		const bool bResult_Back = Do_CanMove (board, pos1, pos0);
		Azzert (bResult_Back == bResult_Forth);
	}
	
	return bResult_Forth;
}

std::string
FigureImpl::GetTypeID
()
const
{
	const std::string sRet = Do_GetTypeID ();
	Azzert (! sRet.empty ());
	return sRet;
}

std::ostream &
FigureImpl::Put
(std::ostream &os)
const
{
	return os << GetTypeID ();
}

std::istream &
FigureImpl::Get
(std::istream &is)
{
	Azzert (is);
	Do_Get (is);
	// [2023-05-15] TODO: Consider whether such debug messages should be displayed at this level.
	if (! is)
		std::cerr << "FigureImpl::Do_Get has failed (" << GetTypeID () << ") !\n";
	return is;
}

std::ostream &operator<< (std::ostream &os, const FigureImpl &figureimpl)
{
	return figureimpl.Put (os);
}

}
