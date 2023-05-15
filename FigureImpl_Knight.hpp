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
};

}
