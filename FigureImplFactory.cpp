#include "FigureImplFactory.hpp"

#include "FigureImpl_Pawn.hpp"
#include "FigureImpl_Rook.hpp"
#include "FigureImpl_Knight.hpp"
#include "FigureImpl_Bishop.hpp"
#include "FigureImpl_Queen.hpp"
#include "FigureImpl_King.hpp"

#include <boost/make_unique.hpp>

namespace Chess1
{

std::unique_ptr <FigureImpl> FigureImplFactory (const boost::string_view &sTypeID)
{
	if      (sTypeID == "pawn"  ) return boost::make_unique <FigureImpl_Pawn>   ();
	else if (sTypeID == "rook"  ) return boost::make_unique <FigureImpl_Rook>   ();
	else if (sTypeID == "knight") return boost::make_unique <FigureImpl_Knight> ();
	else if (sTypeID == "bishop") return boost::make_unique <FigureImpl_Bishop> ();
	else if (sTypeID == "queen" ) return boost::make_unique <FigureImpl_Queen>  ();
	else if (sTypeID == "king"  ) return boost::make_unique <FigureImpl_King>   ();
	else                          return nullptr;
}

}
