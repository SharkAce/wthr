#pragma once

#include "Store.hpp"
#include "Interface.hpp"
#include "Display.hpp"
#include "utils.hpp"

namespace core {

struct Environment {
	Store& store;
	Interface& interface;
	Display& display;
};

} // namespace core
