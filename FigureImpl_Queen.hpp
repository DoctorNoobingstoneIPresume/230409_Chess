#include "FigureImpl.hpp"

namespace Chess1
{

class FigureImpl_Queen:
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
