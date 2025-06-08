#include "../core/Environment.hpp"
#include "../models/TempTimeline.hpp"
#include "../parsing/parsing.hpp"

namespace commands {

void registerSelect(core::Environment& env) {
	core::Interface::Command select {
		[&env](const std::string& args) {
			auto splitArgs = core::utils::tokenise(args, ' ');

			auto scope = parsing::readDataScope(splitArgs[0]);
			auto& scopeState = env.store.get<models::DataScopeState&>("dataScopeState");

			if (env.store.getAll<models::TempTimeline>().empty()) {
				std::cout << "No datasets have been loaded." << std::endl;
				return false;
			}

			if ((int)scope > (int)scopeState.scopeLevel + 1) {
				std::cout << "You are not in the right scope to list " << splitArgs[0] << "s." << std::endl;
				return false;
			}

			// Allow scoping out wihtout specificaiton
			if (splitArgs.size() == 1 && scope < scopeState.scopeLevel) {
				scopeState.scopeLevel = scope;
				return true;
			}

			if (splitArgs.size() != 2) return false;

			const std::string& id = splitArgs[1];
			bool valid = false;

			if (scope == models::DataScope::Country) {
				const auto timelines = env.store.getAll<models::TempTimeline>();
				for (const auto& timeline: timelines) {
					if (timeline.countryCode == id) valid = true;
				}
				if (valid) {
					scopeState.countryCode = id;
					scopeState.scopeLevel = scope;
				}
				return valid;
			}

			const auto& timeline = env.store.get<models::TempTimeline&>(
				scopeState.countryCode + "_timeline"
			);
			
			switch(scope) {
				case models::DataScope::Year:
					for (const auto& dataPoint: timeline.yearlyReadings) {
						if (dataPoint.timestamp.year == std::stoi(id)) valid = true;
					}

					if (valid) {
						scopeState.timeData.year = std::stoi(id);
					}
					break;

				case models::DataScope::Month:
					for (const auto& dataPoint: timeline.monthlyReadings) {
						if (dataPoint.timestamp.year == scopeState.timeData.year &&
								dataPoint.timestamp.month == std::stoi(id)
						) valid = true;
					}

					if (valid) {
						scopeState.timeData.month = std::stoi(id);
					}
					break;

				case models::DataScope::Day:
					for (const auto& dataPoint: timeline.daylyReadings) {
						if (dataPoint.timestamp.year == scopeState.timeData.year &&
								dataPoint.timestamp.month == scopeState.timeData.month &&
								dataPoint.timestamp.day == std::stoi(id)
						) valid = true;
					}

					if (valid) {
						scopeState.timeData.day = std::stoi(id);
					}
					break;

				case models::DataScope::Hour:
					for (const auto& dataPoint: timeline.hourlyReadings) {
						if (dataPoint.timestamp.year == scopeState.timeData.year &&
								dataPoint.timestamp.month == scopeState.timeData.month &&
								dataPoint.timestamp.day == scopeState.timeData.day &&
								dataPoint.timestamp.hour == std::stoi(id)
						) valid = true;
					}

					if (valid) {
						scopeState.timeData.hour = std::stoi(id);
					}
					break;

				default:
					return false;

			}

			if (valid) scopeState.scopeLevel = scope;
			return valid;
		},
		[]() {
			std::cout << "[select]\nUsed to select a scope.\n" 
								<< "Usage: select <scope> <id>\n"
								<< "<id> does not need to be specified when scoping out.\n"
								<< "Avalable scopes are: country, year, month, day, hour" << std::endl;
		}
	};

	env.interface.registerCommand("select", select);
}

} //namespace commands
