#pragma once

#include "../core/Environment.hpp"
#include "../models/TempTimeline.hpp"
#include "../models/DataScope.hpp"

namespace parsing {

bool loadDataset(const std::string& filePath, core::Environment&);
bool validator(const std::string& filePath, core::Environment&);

models::timestamp::Hour readTimestamp(const std::string&);
models::DataScope readDataScope(const std::string&);

} // namespace parsing
