#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include <iostream>

namespace core {

typedef std::function<void(std::string)> Command;

class Interface {
public:
	void run(const std::string& prompt);
	void registerCommand(const std::string& name, Command);


private:
	std::string input;
	void handleCommand(const std::string& input);
	std::unordered_map<std::string, Command> commands;
};

} // namespace core
