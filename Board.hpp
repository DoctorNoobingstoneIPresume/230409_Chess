#pragma once

#include "Figure.hpp"

#include <vector>
#include <iosfwd>

namespace Chess1
{

class Board
{
 private:
	      std::vector <Figure>              _contFigures;

 public:
	std::ostream &Put (std::ostream &os) const;
};

std::ostream &operator<< (std::ostream &os, const Board &object);

}
