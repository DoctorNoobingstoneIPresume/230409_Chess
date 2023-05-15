#include "FigureImpl.hpp"

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

// [2023-05-14 :x]
//bool
//FigureImpl::CanTravelBackAndForth
//()
//const
//{
//	return Do_CanTravelBackAndForth ();
//}
//
//bool
//FigureImpl::CanMove
//(const Board &board, const Position &position0, const Position &position1)
//const
//{
//	Azzert (position1 != position0);
//	//Azzert (board.at (position1).empty ());
//	const bool bResult_Forth = Do_CanMove (board, position0, position1);
//	
//	if (Do_CanTravelBackAndForth ())
//	{
//		const bool bResult_Back = Do_CanMove (board, position1, position0);
//		Azzert (bResult_Back == bResult_Forth);
//	}
//	
//	return bResult_Forth;
//}
//
//bool
//FigureImpl::CanAttack
//(const Board &board, const Position &position0, const Position &position1)
//const
//{
//	return false; // [2023-04-11] TODO !!
//}

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
