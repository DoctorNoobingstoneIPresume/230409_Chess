#pragma once

#include "_Fwd.hpp"

#include <memory>

namespace Chess1
{

class FigureImpl;

std::unique_ptr <FigureImpl> FigureImplFactory (const boost::string_view &sTypeID);

}
