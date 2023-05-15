#include "Board.hpp"
#include "Position.hpp"
#include "Cell.hpp"

#include <iostream>
#include <fstream>

int main (int argc, char **argv)
{
	std::cout << "Hello, World !\n";
	
	using namespace Chess1;
	Board board;
	{
		if (argc < 2)
		{
			std::cerr << "Please specify board !\n";
			return 1;
		}
		
		std::ifstream is (argv [1]);
		if (! is)
		{
			std::cerr << "Board: We have failed to open \"" << argv [1] << "\" for input !\n";
			return 1;
		}
		
		is >> board;
		if (! is)
		{
			std::cerr << "Board: We have failed to read the board from \"" << argv [1] << "\" !\n";
			return 1;
		}
	}
	
	{
		if (argc < 3)
		{
			std::cerr << "Please specify moves !\n";
			return 1;
		}
		
		std::ifstream is (argv [2]);
		if (! is)
		{
			std::cerr << "Moves: We have failed to open \"" << argv [2] << "\" for input !\n";
			return 1;
		}
		
		for (unsigned iPlayer = 0; ; ++iPlayer)
		{
			if (iPlayer >= g_nPlayers)
				iPlayer = 0;
			
			Position pos0;
			{
				is >> pos0;
				if (is.eof ())
					break;
				if (! is)
				{
					std::cerr << "Moves: We have failed to read move (pos0) !\n";
					return 1;
				}
			}
			
			Position pos1;
			{
				is >> pos1;
				if (is.eof ())
				{
					std::cerr << "Moves: Missing second part of move.\n";
					return 1;
				}
				if (! is)
				{
					std::cerr << "Moves: We have failed to read move (pos1) !\n";
					return 1;
				}
			}
			
			std::cout << GetPlayerName (iPlayer) << ": " << pos0 << pos1 << "\n";
			
			Cell &cell0 = board.At (pos0);
			if (cell0.GetPlayer () != iPlayer)
			{
				std::cerr
					<< "Cell " << pos0 << " (" << cell0 << ") should be occupied by " << GetPlayerName (iPlayer)
					<< ", but it is occupied by " << GetPlayerName (cell0.GetPlayer ()) << " !\n";
				return 1;
			}
			
			Cell &cell1 = board.At (pos1);
			if (cell1.GetPlayer () == iPlayer)
			{
				std::cerr
					<< "Cell " << pos1 << " ( " << cell1 << ") should *not* be occupied by " << GetPlayerName (iPlayer)
					<< ", but it is !\n";
				return 1;
			}
			
			if (cell0.CanMove (board, pos0, pos1))
			{
				cell0.BeforeMove (board, pos0, pos1);
				cell1 = std::move (cell0);
			}
			else
			{
				std::cerr << "Cannot perform move (" << cell0.GetTypeID () << ") !\n";
				return 1;
			}
		}
	}
	
	//std::cout << board << "\n";
}
