#include "../core/Environment.hpp"
#include "../models/models.hpp"
#include "../parsing/parsing.hpp"

namespace commands {

void registerList(core::Environment& env) {
	core::Interface::Command list {
		[&env](const std::string& arg) {
			auto scope = parsing::readDataScope(arg);
			auto& scopeState = env.store.get<models::DataScopeState&>("dataScopeState");
			auto& timelines = env.store.get<models::TimelineMap&>("timelines");

			if (scope == models::DataScope::Unset) {
				std::cout << "Invalid scope" << std::endl;
				return false;
			}

			if ((int)scope > (int)scopeState.scopeLevel + 1) {
				std::cout << "You are not in the right scope to list " << arg << "s." << std::endl;
				return false;
			}

			if (scope == models::DataScope::Country) {
				for (const auto& [code, timeline]: timelines) {
					std::cout << code << std::endl;
				}
				return true;
			}

			auto& timeline = timelines.at(scopeState.countryCode);

			switch(scope) {
				case models::DataScope::Year:
					for (auto& [ts, value]: timeline.yearlyReadings) {
						std::cout << ts.year << std::endl;
					}
					break;

				case models::DataScope::Month:
					for (auto& [ts, value]: timeline.monthlyReadings) {
						if (scopeState.timeData.year == ts.year)
							std::cout << ts.month << std::endl;
					}
					break;

				case models::DataScope::Day:
					for (auto& [ts, value]: timeline.dailyReadings) {
						if (
							scopeState.timeData.year == ts.year &&
							scopeState.timeData.month == ts.month
						)
						std::cout << ts.day << std::endl;
					}
					break;

				case models::DataScope::Hour:
					for (auto& [ts, value]: timeline.hourlyReadings) {
						if (
							scopeState.timeData.year == ts.year &&
							scopeState.timeData.month == ts.month &&
							scopeState.timeData.day == ts.day
						)
						std::cout << ts.hour << std::endl;
					}
					break;

				default:
					return false;
			}
			
			return true;
		},
		[]() {
			std::cout << "[list]\nUsed to list available datapoint for each scope.\n"
								<< "Usage: list <scope>\n"
								<< "Avalable scopes are: country, year, month, day, hour" << std::endl;
		}
	};

	env.interface.registerCommand("list", list);
}

} //namespace commands
