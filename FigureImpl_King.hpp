#include "FigureImpl.hpp"

namespace Chess1
{

class FigureImpl_King:
	public FigureImpl
{
 private:
	      unsigned                  _nTeleports;

 public:
	FigureImpl_King
	();

 private:
	FigureImpl *
	Do_Clone
	()
	const
	override;
	
	std::string
	Do_GetTypeID
	()
	const
	override;
	
	std::istream &
	Do_Get
	(std::istream &is)
	override;
	
	bool
	Do_CanMove
	(const Board &board, const Position &pos0, const Position &pos1)
	const
	override;
	
	void
	Do_BeforeMove
	(const Board &board, const Position &pos0, const Position &pos1)
	override;
};

}
