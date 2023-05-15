#include "FigureImpl.hpp"

namespace Chess1
{

class FigureImpl_Knight:
	public FigureImpl
{
 private:
	std::string
	Do_GetTypeID
	()
	const
	override;
	
	bool
	Do_CanMove
	(const Board &board, const Position &pos0, const Position &pos1)
	const
	override;
};

}
