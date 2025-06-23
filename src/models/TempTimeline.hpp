#pragma once

#include <map>
#include "../core/Environment.hpp"
#include "../processing/processing.hpp"
#include "Timestamp.hpp"

namespace models {

typedef std::map<timestamp::Hour, float> HourlyReadings;
typedef std::map<timestamp::Day,float> DailyReadings;
typedef std::map<timestamp::Month, float> MonthlyReadings;
typedef std::map<timestamp::Year, float> YearlyReadings;

class TempTimeline {
public:
	TempTimeline(const std::string& countryCode, HourlyReadings readings);
	std::string countryCode;
	HourlyReadings hourlyReadings;
	DailyReadings dailyReadings;
	MonthlyReadings monthlyReadings;
	YearlyReadings yearlyReadings;

private:
	// I wasn't able to make these using a template because of the key generation
	static DailyReadings groupHoursByDay(const HourlyReadings&);
	static MonthlyReadings groupDaysByMonth(const DailyReadings&);
	static YearlyReadings groupMonthsByYear(const MonthlyReadings&);
};

typedef std::map<std::string, TempTimeline> TimelineMap;

} // namespace models
