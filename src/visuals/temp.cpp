#include "visuals.hpp"
#include "../models/models.hpp"

void visuals::temp(const core::Environment& env) {
	const auto& scopeData = env.store.get<models::DataScopeState&>("dataScopeState");
	const auto& timelines = env.store.get<models::TimelineMap&>("timelines");
	const auto& ts = scopeData.timeData;
	float temp;
	switch(scopeData.scopeLevel) {
		case models::DataScope::Year:
			temp = timelines
				.at(scopeData.countryCode).yearlyReadings
				.at(models::timestamp::Year{ ts.year });
			break;

		case models::DataScope::Month:
			temp = timelines
				.at(scopeData.countryCode).monthlyReadings
				.at(models::timestamp::Month{ ts.year, ts.month });
			break;

		case models::DataScope::Day:
			temp = timelines
				.at(scopeData.countryCode).dailyReadings
				.at(models::timestamp::Day{ ts.year, ts.month, ts.day });
			break;

		case models::DataScope::Hour:
			temp = timelines
				.at(scopeData.countryCode).hourlyReadings.at(ts);
			break;

		default:					
			return;
	}
	std::cout << temp << "C" << std::endl;
}
