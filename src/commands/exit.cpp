#include "../core/Environment.hpp"

namespace commands {

void registerExit(core::Environment& env) {
	core::Interface::Command exit {
		[&env](const std::string&) {
			
			*env.store.get<bool*>("exitPending") = true;
			return true;
		},
		[]() {
			std::cout << "[exit]\nUsed to exit the application." << std::endl;
		}
	};

	env.interface.registerCommand("exit", exit);
}

} //namespace commands
