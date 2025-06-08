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
			auto& timelines = env.store.get<models::TimelineMap&>("timelines");

			if (timelines.empty()) {
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

			// Country needs to be evaluted first so can
			// we define a timeline for other scopes to use.
			if (scope <= models::DataScope::Country) {
				if (core::utils::validateKey(id, timelines)) {
					scopeState.scopeLevel = models::DataScope::Country;
					scopeState.countryCode = id;
					return true;
				}
				return false;
			}

			const auto& timeline = timelines.at(scopeState.countryCode);
			const auto& ts = scopeState.timeData;
			const short sId = std::stoi(id);
			const unsigned short usId = std::stoi(id);
			bool valid = false;

			switch(scope) {
				case models::DataScope::Year:
					if (core::utils::validateKey(
						models::timestamp::Year { sId },
						timeline.yearlyReadings
					)) {
						scopeState.timeData.year = sId;
						valid = true;
					}
					break;

				case models::DataScope::Month:
					if (core::utils::validateKey(
						models::timestamp::Month { ts.year, usId },
						timeline.monthlyReadings
					)) {
						scopeState.timeData.month = usId;
						valid = true;
					}
					break;

				case models::DataScope::Day:
					if (core::utils::validateKey(
						models::timestamp::Day { ts.year, ts.month, usId },
						timeline.dailyReadings
					)) {
						scopeState.timeData.day = usId;
						valid = true;
					}
					break;

				case models::DataScope::Hour:
					if (core::utils::validateKey(
						models::timestamp::Hour { ts.year, ts.month, ts.day, usId },
						timeline.hourlyReadings
					)) {
						scopeState.timeData.hour = usId;
						valid = true;
					}
					break;

				default:					
					valid = false;
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
