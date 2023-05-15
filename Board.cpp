#include "Board.hpp"
#include "Position.hpp"
#include "Cell.hpp"

#include <boost/utility/string_view.hpp>

#include <iostream>
#include <sstream>
#include <iomanip>
#include <locale>
#include <string>

namespace Chess1
{

Board::Board ()
	: _contCells (g_cxBoard * g_cyBoard)
{}

const Cell &Board::At (const Position &pos) const { Azzert (pos.IsValid ()); return _contCells.at (pos.GetY () * g_cxBoard + pos.GetX ()); }
      Cell &Board::At (const Position &pos)       { Azzert (pos.IsValid ()); return _contCells.at (pos.GetY () * g_cxBoard + pos.GetX ()); }

std::ostream &Board::Put (std::ostream &os) const
{
	std::ostringstream osTmp;
	{
		//osTmp << "Board:\n{\n";
		
		for (Coord y = 0; y < g_cyBoard; ++y)
		for (Coord x = 0; x < g_cxBoard; ++x)
		{
			const Position position (x, y);
			const Cell &cell = At (position);
			if (cell.IsOccupied ())
				osTmp << position << ' ' << cell << '\n';
		}
		
		//osTmp << "}\n";
	}
	
	return os << osTmp.str ();
}

std::istream &Board::Get (std::istream &is)
{
	const unsigned _iDebug = 1;
	
	Board board_tmp;
	bool ok = false;
	for (;;)
	{
		std::string sLine;
		{
			getline (is, sLine);
			if (_iDebug) std::cout << "\"" << sLine << "\"\n";
			
			const std::ios_base::iostate state = is.rdstate ();
			if (_iDebug)
				std::cout
					<< (state & std::ios_base::eofbit  ? 'e' : '-')
					<< (state & std::ios_base::failbit ? 'f' : '-')
					<< (state & std::ios_base::badbit  ? 'b' : '-')
					<< '\n';
			
			if (is.eof ())
				{ if (_iDebug) std::cout << "is.eof ()\n"; is.clear (); ok = true; break; }
			
			if (! is)
				{ if (_iDebug) std::cout << "! is\n"; break; }
		}
		
		const std::locale &loc   = is.getloc ();
		const auto        &ctype = std::use_facet <std::ctype <char>> (loc);
		
		boost::string_view svLine (sLine);
		{
			while (! svLine.empty () && ctype.is (std::ctype_base::space, svLine.front ()))
				svLine.remove_prefix (1);
			
			while (! svLine.empty () && ctype.is (std::ctype_base::space, svLine.back  ()))
				svLine.remove_suffix (1);
		}
		
		if (svLine.empty ())
			continue;
		
		std::istringstream isLine (svLine.data ());
		
		Position position;
		{
			isLine >> position;
			if (! isLine)
				break;
		}
		
		if (_iDebug) std::cout << position << "\n";
		
		Cell cell;
		{
			isLine >> cell;
			if (! isLine)
				break;
		}
		
		board_tmp.At (position) = std::move (cell);
	}
	
	if (! ok)
		is.clear (std::ios_base::failbit);
	else
		*this = std::move (board_tmp);
	
	return is;
}

std::ostream &operator<< (std::ostream &os, const Board &board)
{
	return board.Put (os);
}

std::istream &operator>> (std::istream &is,       Board &board)
{
	return board.Get (is);
}

}
