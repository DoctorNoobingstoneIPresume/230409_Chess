#include "FigureImpl.hpp"

namespace Chess1
{

class FigureImpl_Bishop:
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
