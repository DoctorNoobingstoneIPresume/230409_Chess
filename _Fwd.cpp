#include "_Fwd.hpp"

#include <iostream>

#include <cstdlib>

namespace Chess1
{

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
