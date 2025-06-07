#include <map>

#include "../processing/processing.hpp"
#include "TempTimeline.hpp"

namespace models {

TempTimeline::TempTimeline(const std::string& countryCode, HourlyReadings readings):
	countryCode(countryCode),
	hourlyReadings(readings),
	daylyReadings(groupHoursByDay(hourlyReadings)),
	monthlyReadings(groupDaysByMonth(daylyReadings)),
	yearlyReadings(groupMonthByYear(monthlyReadings)) {};

DaylyReadings TempTimeline::groupHoursByDay(const models::HourlyReadings& data) {
	std::map<models::timestamp::Day, std::vector<float>> groups;
	for (const auto& reading: data) {
		auto& ts = reading.timestamp;
		models::timestamp::Day key { ts.year, ts.month, ts.day };
		groups[key].push_back(reading.temp);
	};

models::DaylyReadings output;
	for (const auto& [ts, values]: groups) {
		auto entry = models::TempReading<models::timestamp::Day> {
			ts, core::utils::average(values)
		};
		output.push_back(entry);
	};
	return output;
}

models::MonthlyReadings TempTimeline::groupDaysByMonth(const models::DaylyReadings& data) {
	std::map<models::timestamp::Month, std::vector<float>> groups;
	for (const auto& reading: data) {
		auto& ts = reading.timestamp;
		models::timestamp::Month key { ts.year, ts.month };
		groups[key].push_back(reading.temp);
	};

	models::MonthlyReadings output;
	for (const auto& [ts, values]: groups) {
		auto entry = models::TempReading<models::timestamp::Month> {
			ts, core::utils::average(values)
		};
		output.push_back(entry);
	};
	return output;
}

models::YearlyReadings TempTimeline::groupMonthByYear(const models::MonthlyReadings& data) {
	std::map<models::timestamp::Year, std::vector<float>> groups;
	for (const auto& reading: data) {
		auto& ts = reading.timestamp;
		models::timestamp::Year key { ts.year };
		groups[key].push_back(reading.temp);
	};

	models::YearlyReadings output;
	for (const auto& [ts, values]: groups) {
		auto entry = models::TempReading<models::timestamp::Year> {
			ts, core::utils::average(values)
		};
		output.push_back(entry);
	};
	return output;
}

} // namespace models
