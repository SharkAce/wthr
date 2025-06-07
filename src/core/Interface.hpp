#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include <iostream>

namespace core {

class Interface {
public:
	struct Command {
		std::function<bool(std::string)> action;
		std::function<void()> help;
	};

	void run(const std::string& prompt);
	void registerCommand(const std::string& name, Command);
	const std::unordered_map<std::string, Command>& getCommands() {
		return commands;
	};

private:
	std::string input;
	void handleCommand();
	std::unordered_map<std::string, Command> commands;
};

} // namespace core
