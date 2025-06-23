#include <cmath>
#include "visuals.hpp"
#include "../models/models.hpp"
#include "../processing/processing.hpp"

void visuals::prediction(const core::Environment& env, int predictionCount) {
	auto& scopeState = env.store
		.get<models::DataScopeState&>("dataScopeState");

	auto& t = env.store
		.get<models::TimelineMap&>("timelines")
		.at(scopeState.countryCode);

	int start, end, padding;
	
	std::vector<float> values;
	std::vector<float> predictions;
	std::vector<float> historical;
	int predictionStart;

	const auto& ts = scopeState.timeData;

	switch(scopeState.scopeLevel) {
		case models::DataScope::Country:
			start = t.yearlyReadings.begin()->first.year;
			end = t.yearlyReadings.rbegin()->first.year + predictionCount;
			padding = 2;
			for (auto& [ts, reading]: t.yearlyReadings) {
				values.push_back(reading);
				historical.push_back(reading);
			};
			predictionStart = values.size();
			predictions = processing::predictSeasonal(
				values, 5, 5, predictionCount
			);
			break;

		case models::DataScope::Year:
			start = 1;
			end = 12 + predictionCount;
			predictionCount *= 30;
			padding = 5;
			values = core::utils::getRange(
				models::timestamp::Day(ts.year, 1, 1),
				models::timestamp::Day(ts.year, 12, 31),
				t.dailyReadings
			);
			historical = core::utils::getRange(
				t.dailyReadings.begin()->first,
				models::timestamp::Day(ts.year, 12, 31),
				t.dailyReadings
			);
			predictionStart = values.size();
			predictions = processing::predictSeasonal(
				historical, 365, 30, predictionCount
			);
			break;

		case models::DataScope::Month:
			start = 1;
			end = core::utils::getDaysInMonth(ts.year, ts.month) + predictionCount;
			padding = 2;
			values = core::utils::getRange(
				models::timestamp::Day(ts.year, ts.month, 1),
				models::timestamp::Day(ts.year, ts.month, end),
				t.dailyReadings
			);
			historical = core::utils::getRange(
				t.dailyReadings.begin()->first,
				models::timestamp::Day(ts.year, ts.month, end),
				t.dailyReadings
			);
			predictionStart = values.size();
			predictions = processing::predictSeasonal(
				historical, 365, 7, predictionCount
			);
			break;

		case models::DataScope::Day:
			start = 0;
			end = 23 + predictionCount;
			padding = 2;
			values = core::utils::getRange(
				models::timestamp::Hour(ts.year, ts.month, ts.day, 0),
				models::timestamp::Hour(ts.year, ts.month, ts.day, 23),
				t.hourlyReadings
			);
			historical = core::utils::getRange(
				t.hourlyReadings.begin()->first,
				models::timestamp::Hour(ts.year, ts.month, ts.day, 23),
				t.hourlyReadings
			);
			predictionStart = values.size();
			predictions = processing::predictSeasonal(
				historical, 24, 48, predictionCount
			);
			break;

		default:
			return;
	}

	// Append the predictions to the values
	values.insert(values.end(), predictions.begin(), predictions.end());
	
	float minValue = core::utils::min(values) - padding;
	float maxValue = core::utils::max(values) + padding;
	float valueRange = maxValue - minValue;

	graph(start, end, (int)minValue, (int)maxValue);

	for (unsigned int col = 0; col < cols; ++col) {
		int valueIndex = (values.size() - 1) * col / cols;
		float normalized = (values.at(valueIndex) - minValue) / valueRange;
		int row = std::round(normalized * rows);

		move((rows - row) + offsetY, col + offsetX + 1);

		addch(valueIndex < predictionStart ? 'o' : 'x');
	}
}
