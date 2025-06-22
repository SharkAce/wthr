#pragma once

#include "../core/Environment.hpp"
#include "../models/TempTimeline.hpp"
#include "../models/DataScope.hpp"

namespace parsing {

models::timestamp::Hour readTimestamp(const std::string&);
models::DataScope readDataScope(const std::string&);

bool loadDataset(const std::string& filePath, core::Environment&);
bool validator(const std::string& filePath, core::Environment&);

namespace select {

bool handleCountry(
	const std::string& id,
	const models::TimelineMap& timelines,
	models::DataScopeState& scopeState
);
bool handleDate(
	const std::vector<std::string>& args,
	const models::TempTimeline& timeline,
	models::DataScopeState& scopeState
);
bool handleNumeric(
	const std::string& id,
	models::DataScope scope,
	const models::TempTimeline& timeline,
	models::DataScopeState& scopeState
);

} // namespace parsing::select
} // namespace parsing
