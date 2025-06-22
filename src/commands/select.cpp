#include "../core/Environment.hpp"
#include "../models/models.hpp"
#include "../parsing/parsing.hpp"

namespace commands {

void registerSelect(core::Environment& env) {
	core::Interface::Command select {
		[&env](const std::string& args) {
			auto splitArgs = core::utils::tokenise(args, ' ');
			auto& scopeState = env.store.get<models::DataScopeState&>("dataScopeState");
			auto& timelines = env.store.get<models::TimelineMap&>("timelines");

			if (timelines.empty()) {
				std::cout << "No datasets have been loaded." << std::endl;
				return false;
			}

			if (splitArgs.size() == 0) return false;

			models::DataScope scope;
			if (splitArgs[0] == "date") {
				scope = models::DataScope::Year;
			} else {
				scope = parsing::readDataScope(splitArgs[0]);
				// Allow scoping out wihtout specificaiton
				if (splitArgs.size() == 1 && scope < scopeState.scopeLevel) {
					scopeState.scopeLevel = scope;
					return true;
				}
			}

			if (splitArgs.size() != 2) return false;

			if ((int)scope > (int)scopeState.scopeLevel + 1) {
				std::cout << "You are not in the right scope to select " 
									<< splitArgs[0] << "s." << std::endl;
				return false;
			}

			// Country needs to be evaluted first so we can
			// safely define a timeline for other scopes to use.
			const std::string& id = splitArgs[1];
			if (scope <= models::DataScope::Country) {
				return parsing::select::handleCountry(id, timelines, scopeState);
			}

			const auto& timeline = timelines.at(scopeState.countryCode);

			if (splitArgs[0] == "date") {
				return parsing::select::handleDate(splitArgs, timeline, scopeState);
			}

			return parsing::select::handleNumeric(id, scope, timeline, scopeState);

		},
		[]() {
			std::cout << "[select]\nUsed to select a scope.\n" 
								<< "Usage: select <scope> <id>\n"
								<< "<id> does not need to be specified when scoping out.\n"
								<< "Available scopes are: country, date, year, month, day, hour" << std::endl;
		}
	};

	env.interface.registerCommand("select", select);
}

} //namespace commands
