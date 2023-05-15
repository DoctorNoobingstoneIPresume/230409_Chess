#pragma once

#include "_Fwd.hpp"

namespace Chess1
{

class Board;
class Position;

Coord Coord_AbsDiff (Coord a, Coord b);

bool IsStraightLine (const Board &board, const Position &pos0, const Position &pos1);
bool IsDiagonalLine (const Board &board, const Position &pos0, const Position &pos1);

}
