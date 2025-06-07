#include "../core/Environment.hpp"
#include "../models/models.hpp"
#include "../parsing/parsing.hpp"
#include "../processing/processing.hpp"

namespace commands {

void registerList(core::Environment& env) {
	core::Interface::Command list {
		[&env](const std::string& arg) {
			auto scope = parsing::readDataScope(arg);
			auto scopeState = env.store.get<models::DataScopeState&>("dataScopeState");

			if (scope == models::DataScope::Unset) {
				std::cout << "Invalid scope." << std::endl;
				return false;
			}

			if ((int)scope > (int)scopeState.scopeLevel + 1) {
				std::cout << "You are not in the right scope to list " << arg << "s." << std::endl;
				return false;
			}

			if (scope == models::DataScope::Country) {
				for (auto timeline: env.store.getAll<models::TempTimeline>()) {
					std::cout << timeline.countryCode << std::endl;
				}
				return true;
			}

			int low = 0, high = 0;
			auto timeline = env.store.getAll<models::TempTimeline>()[0].yearlyReadings;

			switch(scope) {
				case models::DataScope::Year:
					low = timeline[0].timestamp.year;
					high = timeline[timeline.size()].timestamp.year;
					break;

				case models::DataScope::Month:
					low = 1;
					high = 12;
					break;

				case models::DataScope::Day:
					low = 1;
					high = processing::daysInMonth(
						(int)scopeState.timeData.year, 
						(int)scopeState.timeData.month
					);
					break;

				case models::DataScope::Hour:
					low = 0;
					high = 23;
					break;

				default:
					return false;
			}

			for (int i = low; i <= high; ++i) {
				std::cout << i << std::endl;
			};
			
			return true;
		},
		[]() {
			std::cout << "[list]\nUsed to list available datapoint for each scope.\n"
								<< "This command assumes complete data for time and date.\n" 
								<< "Avalable scopes are: country, year, month, day, hour" << std::endl;
		}
	};

	env.interface.registerCommand("list", list);
}

} //namespace commands
