#include "_Fwd.hpp"

#include <iostream>
#include <stdexcept>

#include <cstdlib>

namespace Chess1
{

std::string
GetPlayerName
(unsigned iPlayer)
{
	switch (iPlayer)
	{
	 case 0:  { return "white"; }
	 case 1:  { return "black"; }
	 case -1: { return "noone"; }
	 default: { throw std::runtime_error ("Bad player number !"); }
	}
}

[[noreturn]]
void
AzzertionHasFailed_Msg
(
	const boost::string_view &sFileName,
	      unsigned            iLine,
	const boost::string_view &sFunctionName,
	const boost::string_view &sMessage
)
{
	std::cout.flush ();
	std::cerr << "Azzertion has failed (" << sFileName << ":" << iLine << " in function `" << sFunctionName << "`): " << sMessage << "...\n";
	std::abort ();
}

[[noreturn]]
void
AzzertionHasFailed
(
	const boost::string_view &sFileName,
	      unsigned            iLine,
	const boost::string_view &sFunctionName
)
{
	AzzertionHasFailed_Msg (sFileName, iLine, sFunctionName, "(No specific Azzert message.)");
}

}
