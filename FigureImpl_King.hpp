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
	std::string
	Do_GetTypeID
	()
	const
	override;
	
	std::istream &
	Do_Get
	(std::istream &is)
	override;
};

}
