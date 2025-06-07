/*
#include "../core/Environment.hpp"
#include "../models/TempTimeline.hpp"

namespace commands {

void registerList(core::Environment& env) {
	core::Interface::Command list {
		[&env](const std::string& args) {
			auto splitArgs = core::utils::tokenise(args, ' ');
			if (splitArgs.size() != 2) return false;

			if (splitArgs[0] == "country") {
			} else if (splitArgs[1] == "year
			
			return true;
		},
		[]() {
			std::cout << "Used to exit the application" << std::endl;
		}
	};

	env.interface.registerCommand("list", list);
}

} //namespace commands
*/
