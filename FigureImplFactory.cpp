#include "FigureImplFactory.hpp"

#include "FigureImpl_Pawn.hpp"
#include "FigureImpl_Rook.hpp"
#include "FigureImpl_Knight.hpp"
#include "FigureImpl_Bishop.hpp"
#include "FigureImpl_Queen.hpp"
#include "FigureImpl_King.hpp"

#include <boost/make_unique.hpp>

#include <vector>

namespace Chess1
{

std::vector <std::unique_ptr <FigureImpl>> MakePrototypes ()
{
	std::vector <std::unique_ptr <FigureImpl>> vpImpls;
	{
		vpImpls.reserve (6);
		vpImpls.push_back (boost::make_unique <FigureImpl_Pawn>   ());
		vpImpls.push_back (boost::make_unique <FigureImpl_Rook>   ());
		vpImpls.push_back (boost::make_unique <FigureImpl_Knight> ());
		vpImpls.push_back (boost::make_unique <FigureImpl_Bishop> ());
		vpImpls.push_back (boost::make_unique <FigureImpl_Queen>  ());
		vpImpls.push_back (boost::make_unique <FigureImpl_King>   ());
	}
	
	return vpImpls;
}

std::unique_ptr <FigureImpl> FigureImplFactory (const boost::string_view &sTypeID)
{
	// [2023-05-15]
	//if      (sTypeID == "pawn"  ) return boost::make_unique <FigureImpl_Pawn>   ();
	//else if (sTypeID == "rook"  ) return boost::make_unique <FigureImpl_Rook>   ();
	//else if (sTypeID == "knight") return boost::make_unique <FigureImpl_Knight> ();
	//else if (sTypeID == "bishop") return boost::make_unique <FigureImpl_Bishop> ();
	//else if (sTypeID == "queen" ) return boost::make_unique <FigureImpl_Queen>  ();
	//else if (sTypeID == "king"  ) return boost::make_unique <FigureImpl_King>   ();
	//else                          return nullptr;

	static const std::vector <std::unique_ptr <FigureImpl>> vpPrototypes = MakePrototypes ();
	
	for (const auto &p: vpPrototypes)
		if (p->GetTypeID () == sTypeID)
			return p->Clone ();
	
	return nullptr;
}

}
