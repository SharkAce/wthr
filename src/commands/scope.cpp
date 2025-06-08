#include "../core/Environment.hpp"
#include "../models/models.hpp"
#include "../parsing/parsing.hpp"

namespace commands {

void registerScope(core::Environment& env) {
	core::Interface::Command scope {
		[&env](const std::string&) {
			if (env.store.getAll<models::TempTimeline>().empty()) {
				std::cout << "No datasets have been loaded." << std::endl;
				return false;
			}

			auto scopeData = env.store.get<models::DataScopeState&>("dataScopeState");
			auto scopeLevel = scopeData.scopeLevel;

			if (scopeLevel >= models::DataScope::Country) {
				std::cout << "Country: " << scopeData.countryCode << std::endl;
			}
			if (scopeLevel >= models::DataScope::Year) {
				std::cout << "Year: " << scopeData.timeData.year << std::endl;
			}
			if (scopeLevel >= models::DataScope::Month) {
				std::cout << "Month: " << scopeData.timeData.month << std::endl;
			}
			if (scopeLevel >= models::DataScope::Day) {
				std::cout << "Day: " << scopeData.timeData.day << std::endl;
			}
			if (scopeLevel >= models::DataScope::Hour) {
				std::cout << "Hour: " << scopeData.timeData.hour << std::endl;
			}
			
			return true;
		},
		[]() {
			std::cout << "[scope]\nUsed to get info on the current scope." << std::endl;
		}
	};

	env.interface.registerCommand("scope", scope);
}

} //namespace commands
