#include <map>

#include "../processing/processing.hpp"
#include "TempTimeline.hpp"

namespace models {

TempTimeline::TempTimeline(const std::string& countryCode, HourlyReadings readings):
	countryCode(countryCode),
	hourlyReadings(readings),
	dailyReadings(groupHoursByDay(hourlyReadings)),
	monthlyReadings(groupDaysByMonth(dailyReadings)),
	yearlyReadings(groupMonthByYear(monthlyReadings)) {};

DailyReadings TempTimeline::groupHoursByDay(const HourlyReadings& data) {
	std::map<timestamp::Day, std::vector<float>> groups;
	for (const auto& [ts, temp]: data) {
		timestamp::Day key { ts.year, ts.month, ts.day };
		groups[key].push_back(temp);
	};

	DailyReadings output;
	for (const auto& [ts, values]: groups) {
		output[ts] = core::utils::average(values);
	};
	return output;
}

MonthlyReadings TempTimeline::groupDaysByMonth(const DailyReadings& data) {
	std::map<timestamp::Month, std::vector<float>> groups;
	for (const auto& [ts, temp]: data) {
		timestamp::Month key { ts.year, ts.month };
		groups[key].push_back(temp);
	};

	MonthlyReadings output;
	for (const auto& [ts, values]: groups) {
		output[ts] = core::utils::average(values);
	};
	return output;
}

YearlyReadings TempTimeline::groupMonthByYear(const MonthlyReadings& data) {
	std::map<timestamp::Year, std::vector<float>> groups;
	for (const auto& [ts, temp]: data) {
		timestamp::Year key { ts.year };
		groups[key].push_back(temp);
	};

	YearlyReadings output;
	for (const auto& [ts, values]: groups) {
		output[ts] = core::utils::average(values);
	};
	return output;
}

} // namespace models
