#include "Interface.hpp"
#include "utils.hpp"

namespace core {

void Interface::run(const std::string& prompt) {
	std::cout << prompt;
	std::getline(std::cin, input);
	handleCommand();
	input = "";
}

void Interface::handleCommand() {
	if (input == "") return;

	auto spacePos = input.find(' ');
	std::string command = spacePos == std::string::npos ? input : input.substr(0, spacePos);
	std::string argument = spacePos == std::string::npos ? "" : input.substr(spacePos + 1);

	if (utils::validateKey(command, commands)) {
		if (!commands[command].action(argument)) {
			std::cout << command << " failed" << std::endl;
			commands[command].help();
		}
	} else {
		std::cout << "Avalable commands are:" << std::endl;
		for (auto command: getCommands()) {
			std::cout << command.first << std::endl;
		}
	}
};

void Interface::registerCommand(const std::string &name, Command command) {
	commands[name] = command;
}

} // namespace core
