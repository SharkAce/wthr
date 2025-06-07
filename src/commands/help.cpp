#include "../core/Environment.hpp"

namespace commands {

void registerHelp(core::Environment& env) {
	core::Interface::Command help {
		[&env](const std::string& arg) {
			if (arg.empty()) {
				std::cout << "Available commands:" << std::endl;
				for (auto command: env.interface.getCommands()) {
					std::cout << command.first << std::endl;
				}
			} else {
				if (!core::utils::validateKey(arg, env.interface.getCommands())) return false;
				env.interface.getCommands().at(arg).help();
			}
			return true;
		},
		[&env]() {
			std::cout << "[help]:\nGives info on how to use the different commands.\n"
								<< "Available arguments:" << std::endl;
			for (auto command: env.interface.getCommands()) {
				std::cout << command.first << std::endl;
			}
		}
	};
	env.interface.registerCommand("help", help);
}

} //namespace commands
