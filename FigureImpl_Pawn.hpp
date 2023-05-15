#include "FigureImpl.hpp"

namespace Chess1
{

class FigureImpl_Pawn:
	public FigureImpl
{
 private:
	bool
	Do_CanTravelBackAndForth
	()
	const
	override;
	
	bool
	Do_CanMove
	(const Board &board, const Position &pos0, const Position &pos1)
	const
	override;
	
	std::string
	Do_GetTypeID
	()
	const
	override;
};

}
