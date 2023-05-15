#include "FigureImpl_King.hpp"

namespace Chess1
{

FigureImpl_King::FigureImpl_King
():
	_nTeleports (2)
{}

std::string
FigureImpl_King::Do_GetTypeID
()
const
{
	return "king";
}

std::istream &
FigureImpl_King::Do_Get
(std::istream &is)
{
	is >> _nTeleports;
	return is;
}

}
