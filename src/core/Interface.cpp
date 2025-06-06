#include "Interface.hpp"

namespace core {

void Interface::run(const std::string& prompt) {
	std::cout << prompt;
	std::getline(std::cin, input);
	handleCommand(input);
	input = "";
}

void Interface::handleCommand(const std::string& input) {
	auto spacePos = input.find(' ');
	std::string command = spacePos == std::string::npos ? input : input.substr(0, spacePos);
	std::string argument = spacePos == std::string::npos ? "" : input.substr(spacePos + 1);

	commands[command](argument);
};

void Interface::registerCommand(const std::string &name, Command command) {
	commands[name] = command;
}

} // namespace core
