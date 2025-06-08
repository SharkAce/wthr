#include "../core/Environment.hpp"

namespace commands {

void registerShow(core::Environment& env) {
	core::Interface::Command show {
		[&env](const std::string& arg) {
			if (arg == "canddle") {};
			if (arg == "plot") {};
			if (arg == "prediciton") {};
			
			return true;
		},
		[]() {
			std::cout << "Used to exit the application" << std::endl;
		}
	};

	env.interface.registerCommand("show", show);
}

} //namespace commands
