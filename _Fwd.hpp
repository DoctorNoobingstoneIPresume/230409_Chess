#pragma once

#include "_FwdConfig.hpp"

#include <boost/utility/string_view.hpp>

#include <string>

#include <stdint.h>

namespace Chess1
{

// [2023-05-15] conmv: Like const (for the purpose of self-documenting), except that it might be moved-from at some point.
#ifndef conmv
 #define conmv
#endif

typedef unsigned Coord;
const Coord g_cxBoard = 8;
const Coord g_cyBoard = 8;
const Coord g_xSpecial = -1, g_xError = -2;
const Coord g_ySpecial = -1, g_yError = -2;

constexpr bool IsValidX   (Coord x) { return x < g_cxBoard; }
constexpr bool IsValidY   (Coord y) { return y < g_cyBoard; }
constexpr bool IsSpecialX (Coord x) { return x == g_xSpecial; }
constexpr bool IsSpecialY (Coord y) { return y == g_ySpecial; }

const unsigned g_nPlayers = 2;
std::string GetPlayerName (unsigned iPlayer);
constexpr bool IsValidPlayer (unsigned iPlayer) { return iPlayer < g_nPlayers; }

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
