#include <cmath>
#include "visuals.hpp"
#include "../models/models.hpp"

void visuals::plot(const core::Environment& env) {
	auto& scopeState = env.store
		.get<models::DataScopeState&>("dataScopeState");

	auto& t = env.store
		.get<models::TimelineMap&>("timelines")
		.at(scopeState.countryCode);

	int start, end, padding;
	
	std::vector<float> values;

	const auto& ts = scopeState.timeData;

	switch(scopeState.scopeLevel) {
		case models::DataScope::Country:
			start = t.yearlyReadings.begin()->first.year;
			end = t.yearlyReadings.rbegin()->first.year;
			padding = 2;
			for (auto& [ts, reading]: t.yearlyReadings) {
				values.push_back(reading);
			};
			break;

		case models::DataScope::Year:
			start = 1;
			end = 12;
			padding = 5;
			values = core::utils::getRange(
				models::timestamp::Day(ts.year, 1, 1),
				models::timestamp::Day(ts.year, 12, 31),
				t.dailyReadings
			);
			break;

		case models::DataScope::Month:
			start = 1;
			end = core::utils::getDaysInMonth(ts.year, ts.month);
			padding = 2;
			values = core::utils::getRange(
				models::timestamp::Day(ts.year, ts.month, 1),
				models::timestamp::Day(ts.year, ts.month, end),
				t.dailyReadings
			);
			break;

		case models::DataScope::Day:
			start = 0;
			end = 23;
			padding = 2;
			values = core::utils::getRange(
				models::timestamp::Hour(ts.year, ts.month, ts.day, 0),
				models::timestamp::Hour(ts.year, ts.month, ts.day, 23),
				t.hourlyReadings
			);
			break;

		default:
			return;
	}
	
	float minValue = core::utils::min(values) - padding;
	float maxValue = core::utils::max(values) + padding;
	float valueRange = maxValue - minValue;

	graph(start, end, (int)minValue, (int)maxValue);

	for (unsigned int col = 0; col < cols; ++col) {
		int valueIndex = (values.size() - 1) * col / cols;
		float normalized = (values.at(valueIndex) - minValue) / valueRange;
		int row = std::round(normalized * rows);

		move((rows - row) + offsetY, col + offsetX + 1);
		addch('o');
	}
}
