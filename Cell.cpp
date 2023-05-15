#include "Cell.hpp"

#include "FigureImpl.hpp"
#include "FigureImplFactory.hpp"

#include <boost/core/exchange.hpp>

#include <iostream>
#include <sstream>
#include <iomanip>
#include <utility>

namespace Chess1
{

Cell::~Cell
()
= default;

void
Cell::Swap
(Cell &rhs)
noexcept
{
	using std::swap;
	swap (_pImpl  , rhs._pImpl  );
	swap (_iPlayer, rhs._iPlayer);
}

Cell::Cell
(Cell &&rhs)
noexcept:
	_pImpl   (std::move       (rhs._pImpl)),
	_iPlayer (boost::exchange (rhs._iPlayer, -1))
{}

Cell &
Cell::operator=
(Cell &&rhs)
noexcept
{
	Cell tmp (std::move (rhs));
	Swap (tmp);
	return *this;
}

Cell::Cell
():
	_iPlayer (-1)
{}

Cell::Cell
(std::unique_ptr <FigureImpl> pImpl, unsigned iPlayer):
	_pImpl   (std::move (pImpl)),
	_iPlayer (iPlayer)
{
	// [2023-05-15]
	//std::cout << "Cell::Cell (\"" << (pImpl ? pImpl->GetTypeID () : "---") << "\")\n";
	Azzert (IsValidPlayer (_iPlayer) == ! ! _pImpl);
}

unsigned
Cell::GetPlayer
()
const
{
	return _iPlayer;
}

bool
Cell::IsOccupied
()
const
{
	return IsValidPlayer (_iPlayer);
}

std::string
Cell::GetTypeID
()
const
{
	return _pImpl->GetTypeID ();
}

bool
Cell::CanMove
(const Board &board, const Position &pos0, const Position &pos1)
const
{
	return _pImpl->CanMove (board, pos0, pos1);
}

void
Cell::BeforeMove
(const Board &board, const Position &pos0, const Position &pos1)
{
	return _pImpl->BeforeMove (board, pos0, pos1);
}

//const FigureImpl *
//Cell::AdrImpl
//()
//const
//{
//	return _pImpl.get ();
//}
//
//FigureImpl *
//Cell::AdrImpl
//()
//{
//	return _pImpl.get ();
//}

std::ostream &Cell::Put (std::ostream &os) const
{
	std::ostringstream osTmp;
	{
		if (IsValidPlayer (_iPlayer))
		{
			Azzert (_pImpl);
			osTmp << GetPlayerName (_iPlayer) << ' ' << *_pImpl;
		}
		else
		{
			Azzert (! _pImpl);
			osTmp << '-';
		}
	}
	
	return os << osTmp.str ();
}

std::istream &Cell::Get (std::istream &is)
{
	std::string sPlayer;
	{
		is >> sPlayer;
		if (! is)
			return is;
		std::cout << " (sPlayer \"" << sPlayer << "\")";
	}
	
	unsigned iPlayer = -1;
	{
		for (unsigned jPlayer = 0; jPlayer < g_nPlayers; ++jPlayer)
			if (sPlayer == GetPlayerName (jPlayer))
				{ iPlayer = jPlayer; break; }
	}
	
	// [2023-05-15] TODO: Support for "Get"-ting empty Cells ?
	Azzert (IsValidPlayer (iPlayer));
	
	std::string sTypeID;
	{
		is >> sTypeID;
		if (! is)
			return is;
		std::cout << " (sTypeID " << sTypeID << ")";
	}
	
	std::unique_ptr <FigureImpl> pImpl = FigureImplFactory (sTypeID);
	// [2023-05-15] TODO: Support bad type ID ?
	Azzert (pImpl);
	
	pImpl->Get (is);
	if (! is)
	{
		std::cerr << "FigureImpl::Get has failed !\n";
		return is;
	}
	
	Cell tmp (std::move (pImpl), iPlayer);
	Swap (tmp);
	
	return is;
}

std::ostream &operator<< (std::ostream &os, const Cell &cell) { return cell.Put (os); }
std::istream &operator>> (std::istream &is,       Cell &cell) { return cell.Get (is); }

}
