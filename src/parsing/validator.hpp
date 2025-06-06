#pragma once

#include "validator.hpp"
#include "../core/Environment.hpp"

namespace parsing {

bool validator(const std::string& filePath, core::Environment&);

} // namespace parsing
