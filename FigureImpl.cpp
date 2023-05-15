#include "FigureImpl.hpp"
#include "Board.hpp"
#include "Cell.hpp"

#include <iostream>
#include <typeinfo>

namespace Chess1
{

FigureImpl::~FigureImpl
()
{}

FigureImpl::FigureImpl
(const FigureImpl &rhs)
= default;

FigureImpl::FigureImpl
()
= default;

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

void
FigureImpl::Do_BeforeMove
(const Board &board, const Position &pos0, const Position &pos1)
{}

std::unique_ptr <FigureImpl>
FigureImpl::Clone
()
const
{
	FigureImpl *const p = Do_Clone ();
	Azzert (p);
	//std::cout << typeid (*p).name () << " is a clone of " << typeid (*this).name () << "...\n";
	Azzert (typeid (*p) == typeid (*this));
	return std::unique_ptr <FigureImpl> (p);
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

void
FigureImpl::BeforeMove
(const Board &board, const Position &pos0, const Position &pos1)
{
	Azzert (CanMove (board, pos0, pos1));
	return Do_BeforeMove (board, pos0, pos1);
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
