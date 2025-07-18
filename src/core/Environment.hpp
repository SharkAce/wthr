#pragma once

#include "Store.hpp"
#include "Interface.hpp"
#include "utils.hpp"

namespace core {

struct Environment {
	Store& store;
	Interface& interface;
};

} // namespace core
