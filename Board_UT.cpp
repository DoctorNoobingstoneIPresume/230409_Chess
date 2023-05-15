#include "Board.hpp"

#include <iostream>
#include <sstream>

int main ()
{
	using namespace Chess1;
	
	Board board;
	{
		std::istringstream is
		(
			"A1 white rook\n"
			"B1 white knight\n"
		);
		
		is >> board;
		Azzert (is);
	}
	
	std::cout << "Board:\n{\n" << board << "}\n\n";
}
