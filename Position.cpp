#include "Position.hpp"

#include <iostream>
#include <locale>

namespace Chess1
{

Coord Position::GetX () const { return _x; }
Coord Position::GetY () const { return _y; }
bool Position::IsValid () const { return IsValidX (_x) && IsValidY (_y); }

Position &Position::SetX (Coord value) { _x = value; return *this; }
Position &Position::SetY (Coord value) { _y = value; return *this; }

Position::Position (Coord x, Coord y):
	_x (x),
	_y (y)
{
	Azzert (IsValidX (x) || IsSpecialX (x));
	Azzert (IsValidY (y) || IsSpecialY (y));
}

namespace
{
	const char *const names_for_x = "?ABCDEFGH";
	const char *const names_for_y = "?12345678";
	
	const char
		x_name_base_lower = 'a', x_name_base_upper = 'A', x_name_special = '?',
		y_name_base_lower = '1', y_name_base_upper = '1', y_name_special = '?';
	
	Coord char_to_x (char c)
	{
		if (c >= x_name_base_lower && c < x_name_base_lower + g_cxBoard)
			return c - x_name_base_lower;
		else
		if (c >= x_name_base_upper && c < x_name_base_upper + g_cxBoard)
			return c - x_name_base_upper;
		else
		if (c == x_name_special)
			return g_xSpecial;
		else
			return g_xError;
	}
	
	Coord char_to_y (char c)
	{
		if (c >= y_name_base_lower && c < y_name_base_lower + g_cyBoard)
			return c - y_name_base_lower;
		else
		if (c >= y_name_base_upper && c < y_name_base_upper + g_cyBoard)
			return c - y_name_base_upper;
		else
		if (c == y_name_special)
			return g_ySpecial;
		else
			return g_yError;
	}
}

std::ostream &Position::Put (std::ostream &os) const
{
	const char ac [3] =
	{
		IsValidX (_x) ? static_cast <char> (_x + x_name_base_upper) : x_name_special,
		IsValidY (_y) ? static_cast <char> (_y + y_name_base_upper) : y_name_special,
		0 // Redundantly specified for (debatable) clarity.
	};
	
	return os << ac;
}

std::istream &Position::Get (std::istream &is)
{
	Coord x  = g_xSpecial;
	Coord y  = g_ySpecial;
	bool  ok = false;
	{
		const std::locale &loc = is.getloc ();
		const auto &ctype = std::use_facet <std::ctype <char>> (loc);
		for (unsigned iState = 0; ; )
		{
			const char c = is.get ();
			if (! is)
				break;
			else
			if (! iState)
			{
				if (ctype.is (std::ctype_base::space, c))
					continue;
				
				x = char_to_x (c);
				if (! IsValidX (x))
					break;
				
				iState = 1;
			}
			else
			if (iState == 1)
			{
				y = char_to_y (c);
				if (! IsValidY (y))
					break;
				
				ok = true;
				break;
			}
			else
				Azzert (0);
		}
	}
	
	if (ok)
	{
		_x = x;
		_y = y;
	}
	else
		is.clear (std::ios_base::failbit);
	
	return is;
}

std::ostream &operator<< (std::ostream &os, const Position &object)
{
	return object.Put (os);
}

std::istream &operator>> (std::istream &is,       Position &object)
{
	return object.Get (is);
}

bool operator== (const Position &object0, const Position &object1)
{
	return
		object0.GetX () == object1.GetX ()
		&&
		object0.GetY () == object1.GetY ();
}

bool operator!= (const Position &object0, const Position &object1)
{
	return ! (object0 == object1);
}

}
