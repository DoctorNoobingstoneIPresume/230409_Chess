#pragma once

#include <boost/utility/string_view.hpp>

#include <stdint.h>

namespace Chess1
{

typedef unsigned Coord;
const Coord g_cxBoard = 8;
const Coord g_cyBoard = 8;

const unsigned g_nPlayers = 2;

[[noreturn]]
void
AzzertionHasFailed_Msg
(
	const boost::string_view &sFileName,
	      unsigned            iLine,
	const boost::string_view &sFunctionName,
	const boost::string_view &sMessage
);

[[noreturn]]
void
AzzertionHasFailed
(
	const boost::string_view &sFileName,
	      unsigned            iLine,
	const boost::string_view &sFunctionName
);

#define Azzert_Msg(bCondition, sMessage) do { if (! (bCondition)) AzzertionHasFailed_Msg (__FILE__, __LINE__, __func__, sMessage); } while (0)
#define Azzert(bCondition)               do { if (! (bCondition)) AzzertionHasFailed     (__FILE__, __LINE__, __func__          ); } while (0)

}
