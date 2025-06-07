#include "../core/Environment.hpp"

namespace commands {

void registerShow(core::Environment& env) {
	core::Interface::Command show {
		[&env](const std::string&) {
			
			return true;
		},
		[]() {
			std::cout << "Used to exit the application" << std::endl;
		}
	};

	env.interface.registerCommand("show", show);
}

} //namespace commands
