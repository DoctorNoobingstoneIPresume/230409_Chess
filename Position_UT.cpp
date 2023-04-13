#include "Position.hpp"

#include <iostream>
#include <sstream>
#include <string>

int main ()
{
	using namespace Chess1;
	
	for (Coord x = 0; x < g_cxBoard; ++x)
		for (Coord y = 0; y < g_cyBoard; ++y)
		{
			const Position pos (x, y);
			
			std::string s;
			{
				std::ostringstream os; { os << pos; }
				s = os.str ();
			}
			
			//std::cout << s << '\n';
			Azzert (s.size () == 2);
			Azzert (s [0] == 'A' + x);
			Azzert (s [1] == '1' + y);
		}
}
