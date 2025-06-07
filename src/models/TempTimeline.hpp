#pragma once

#include <vector>
#include "../core/Environment.hpp"
#include "../processing/processing.hpp"
#include "Timestamp.hpp"

namespace models {

template<typename TimestampType>
struct TempReading {
	TimestampType timestamp;
	float temp;
};

typedef std::vector<TempReading<timestamp::Hour>> HourlyReadings;
typedef std::vector<TempReading<timestamp::Day>> DaylyReadings;
typedef std::vector<TempReading<timestamp::Month>> MonthlyReadings;
typedef std::vector<TempReading<timestamp::Year>> YearlyReadings;

class TempTimeline {
public:
	TempTimeline(const std::string& countryCode, HourlyReadings readings);
	std::string countryCode;
	HourlyReadings hourlyReadings;
	DaylyReadings daylyReadings;
	MonthlyReadings monthlyReadings;
	YearlyReadings yearlyReadings;

private:
	static DaylyReadings groupHoursByDay(const HourlyReadings&);
	static MonthlyReadings groupDaysByMonth(const DaylyReadings&);
	static YearlyReadings groupMonthByYear(const MonthlyReadings&);
};

} // namespace models
