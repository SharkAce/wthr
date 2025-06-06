#pragma once

#include "validator.hpp"
#include "../core/Environment.hpp"
#include "../models/TempTimeline.hpp"

namespace parsing {

void loadDataset(const std::string& filePath, core::Environment&);

models::Timestamp readTimestamp(const std::string&);

} // namespace parsing
