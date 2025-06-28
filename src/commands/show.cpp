#include <ncurses.h>

#include "../core/Environment.hpp"
#include "../models/models.hpp"
#include "../visuals/visuals.hpp"
#include "../parsing/parsing.hpp"

namespace commands {

void registerShow(core::Environment& env) {
	core::Interface::Command show {
		[&env](const std::string& args) {
			auto& scopeState = env.store.get<models::DataScopeState&>("dataScopeState");
			if (scopeState.scopeLevel < models::DataScope::Country) {
				std::cout << "No country selected." << std::endl;
				return false;
			}

			auto splitArgs = core::utils::tokenise(args, ' ');
			if (splitArgs.size() == 0) {
				std::cout << "Please select a visual mode." << std::endl;
				return false;
			}

			models::VisualMode visualMode = parsing::readVisualMode(splitArgs[0]);

			switch (visualMode) {
				case models::VisualMode::temp:
					if (scopeState.scopeLevel <= models::DataScope::Country) {
						std::cout << "Scope level is too low." << std::endl;
						return false;
					}

					visuals::temp(env);
					return true;

				case models::VisualMode::plot:
					if (scopeState.scopeLevel >= models::DataScope::Hour) {
						std::cout << "Scope level is too high." << std::endl;
						return false;
					}

					initscr();
					visuals::plot(env);
					core::utils::leaveScrOnInput();
					return true;

				case models::VisualMode::prediction:
					if (scopeState.scopeLevel >= models::DataScope::Hour) {
						std::cout << "Scope level is too high." << std::endl;
						return false;
					}

					initscr();
					visuals::prediction(
						env, splitArgs.size() == 2 ? std::stoi(splitArgs[1]) : 12
					);
					core::utils::leaveScrOnInput();
					return true;

				case models::VisualMode::candlestick:
					if (scopeState.scopeLevel >= models::DataScope::Day) {
						std::cout << "Scope level is too high." << std::endl;
						return false;
					}

					initscr();
					visuals::candlesticks(env);
					core::utils::leaveScrOnInput();
					return true;
				
				case models::VisualMode::invalid:
					std::cout << "Select a valid mode." << std::endl;
					return false;
			}
			return false;
		},
		[]() {
			std::cout << "[show]\nUsed to display temperature data.\n"
								<< "Available visuals are: temp, plot, prediction, candles" << std::endl;
		}
	};

	env.interface.registerCommand("show", show);
}

} //namespace commands
