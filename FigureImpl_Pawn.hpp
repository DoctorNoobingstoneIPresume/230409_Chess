#include "FigureImpl.hpp"

namespace Chess1
{

class FigureImpl_Pawn:
	public FigureImpl
{
 private:
	std::string
	Do_GetTypeID
	()
	const
	override;
};

}
