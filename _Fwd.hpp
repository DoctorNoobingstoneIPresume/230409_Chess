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

}

#define Chess1_Azzert_Msg(bCondition, sMessage) do { if (! (bCondition)) Chess1::AzzertionHasFailed_Msg (__FILE__, __LINE__, __func__, sMessage); } while (0)
#define Chess1_Azzert(bCondition)               do { if (! (bCondition)) Chess1::AzzertionHasFailed     (__FILE__, __LINE__, __func__          ); } while (0)

#ifndef CHESS1_NO_UNAFFIXED_AZZERT
	#define Azzert_Msg Chess1_Azzert_Msg
	#define Azzert     Chess1_Azzert
#endif
