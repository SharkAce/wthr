#include <cmath>
#include "visuals.hpp"
#include "../models/models.hpp"

void visuals::plot(const core::Environment& env) {
	auto& s = env.store
		.get<models::DataScopeState&>("dataScopeState");

	auto& t = env.store
		.get<models::TimelineMap&>("timelines")
		.at(s.countryCode);

	int start, end, padding;
	
	std::vector<float> values;

	switch(s.scopeLevel) {
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
			for (auto& [ts, reading]: t.dailyReadings) {
				if (ts.year == s.timeData.year) values.push_back(reading);
			}
			break;

		case models::DataScope::Month:
			start = 1;
			end = 28;
			padding = 2;
			for (auto& [ts, reading]: t.dailyReadings) {
				if (
					ts.year != s.timeData.year || 
					ts.month != s.timeData.month
				) continue;

				if (ts.day > end) end = ts.day;
				values.push_back(reading);
			}
			break;

		case models::DataScope::Day:
			start = 0;
			end = 23;
			padding = 2;
			for (auto& [ts, reading]: t.hourlyReadings) {
				if (
					ts.year == s.timeData.year && 
					ts.month == s.timeData.month && 
					ts.day == s.timeData.day
				) values.push_back(reading);
			}
			break;

		default:
			return;
	}
	
	float minValue = core::utils::min(values) - padding;
	float maxValue = core::utils::max(values) + padding;
	float valueRange = maxValue - minValue;

	visuals::graph(start, end, (int)minValue, (int)maxValue);

	for (unsigned int col = 0; col < visuals::cols; ++col) {
		int valueIndex = (values.size() - 1) * col / visuals::cols;
		float normalized = (values.at(valueIndex) - minValue) / valueRange;
		int row = std::round(normalized * visuals::rows);

		move((visuals::rows - row) + visuals::offsetY, col + visuals::offsetX + 1);
		printw("o");
	}
}
