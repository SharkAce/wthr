#include "../core/Environment.hpp"
#include "../models/models.hpp"
#include "../parsing/parsing.hpp"

namespace commands {

void registerList(core::Environment& env) {
	core::Interface::Command list {
		[&env](const std::string& arg) {
			auto scope = parsing::readDataScope(arg);
			auto scopeState = env.store.get<models::DataScopeState&>("dataScopeState");

			if (scope == models::DataScope::Unset) {
				std::cout << "Invalid scope" << std::endl;
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

			auto timeline = env.store.get<models::TempTimeline>(
				scopeState.countryCode + "_timeline"
			);
			auto MonthlyReadings = env.store.getAll<models::TempTimeline>()[0].yearlyReadings;

			switch(scope) {
				case models::DataScope::Year:
					for (auto& reading: timeline.yearlyReadings) {
						std::cout << reading.timestamp.year << std::endl;
					}
					break;

				case models::DataScope::Month:
					for (auto& reading: timeline.monthlyReadings) {
						if (scopeState.timeData.year == reading.timestamp.year)
							std::cout << reading.timestamp.month << std::endl;
					}
					break;

				case models::DataScope::Day:
					for (auto& reading: timeline.daylyReadings) {
						if (
							scopeState.timeData.year == reading.timestamp.year &&
							scopeState.timeData.month == reading.timestamp.month
						)
						std::cout << reading.timestamp.day << std::endl;
					}
					break;

				case models::DataScope::Hour:
					for (auto& reading: timeline.hourlyReadings) {
						if (
							scopeState.timeData.year == reading.timestamp.year &&
							scopeState.timeData.month == reading.timestamp.month &&
							scopeState.timeData.day == reading.timestamp.day
						)
						std::cout << reading.timestamp.hour << std::endl;
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
