#include "../core/Environment.hpp"
#include "../models/models.hpp"

namespace commands {

void registerShow(core::Environment& env) {
	core::Interface::Command show {
		[&env](const std::string& arg) {
			if (arg == "canddle") {}
			else if (arg == "plot") {}
			else if (arg == "prediciton") {}
			else if (arg == "temp") {
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
						return false;
				}
				std::cout << temp << "°" << std::endl;

			} else return false;

			return true;
		},
		[]() {
			std::cout << "[show]\nUsed to display temp data." << std::endl;
		}
	};

	env.interface.registerCommand("show", show);
}

} //namespace commands
