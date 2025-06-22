#include "parsing.hpp"

namespace parsing::select {

bool handleCountry (
	const std::string& id, 
	const models::TimelineMap& timelines, 
	models::DataScopeState& scopeState
) {
	if (!core::utils::validateKey(id, timelines)) {
		std::cout << "Country not found." << std::endl;
		return false;
	}
	scopeState.scopeLevel = models::DataScope::Country;
	scopeState.countryCode = id;
	return true;
}

bool handleDate(
	const std::vector<std::string>& args, 
	const models::TempTimeline& timeline,
	models::DataScopeState& scopeState
) {
	auto components = core::utils::tokenise(args[1], '/');
	if (components.size() != 3) {
		std::cout << "Invalid date format. Use dd/mm/yyyy" << std::endl;
		return false;
	}

	models::timestamp::Day dateTs { 
		(short)std::stoi(components[2]),
		(unsigned short)std::stoi(components[1]),
		(unsigned short)std::stoi(components[0])
	};

	if (!core::utils::validateKey(dateTs, timeline.dailyReadings)) {
		std::cout << "No data available for that date." << std::endl;
		return false;
	} else {
		scopeState.timeData.day = dateTs.day;
		scopeState.timeData.month = dateTs.month;
		scopeState.timeData.year = dateTs.year;
		scopeState.scopeLevel = models::DataScope::Day;
	}
	return true;
}

bool handleNumeric(
	const std::string& id,
	const models::DataScope scope,
	const models::TempTimeline& timeline,
	models::DataScopeState& scopeState
) {
	const unsigned short idValue = std::stoi(id);
	auto& ts = scopeState.timeData;
	bool valid = false;

	switch(scope) {
		case models::DataScope::Year:
			if (core::utils::validateKey(
						models::timestamp::Year { (short)idValue },
						timeline.yearlyReadings
						)) {
				ts.year = (short)idValue;
				valid = true;
			}
			break;

		case models::DataScope::Month:
			if (core::utils::validateKey(
						models::timestamp::Month { ts.year, idValue },
						timeline.monthlyReadings
						)) {
				ts.month = idValue;
				valid = true;
			}
			break;

		case models::DataScope::Day:
			if (core::utils::validateKey(
						models::timestamp::Day { ts.year, ts.month, idValue },
						timeline.dailyReadings
						)) {
				ts.day = idValue;
				valid = true;
			}
			break;

		case models::DataScope::Hour:
			if (core::utils::validateKey(
						models::timestamp::Hour { ts.year, ts.month, ts.day, idValue },
						timeline.hourlyReadings
						)) {
				ts.hour = idValue;
				valid = true;
			}
			break;

		default:					
			break;
	}

	if (valid) { 
		scopeState.scopeLevel = scope;
	} else {
		std::cout << "No data available for that timestamp." << std::endl;
	};
	return valid;
}

} // namespace parsing::select
