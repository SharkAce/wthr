#include <ncurses.h>

#include "../core/Environment.hpp"
#include "../models/models.hpp"
#include "../visuals/visuals.hpp"

namespace commands {

void registerShow(core::Environment& env) {
	core::Interface::Command show {
		[&env](const std::string& args) {
			auto& scopeState = env.store.get<models::DataScopeState&>("dataScopeState");
			if (scopeState.scopeLevel < models::DataScope::Country) {
				std::cout << "No dataset loaded." << std::endl;
				return false;
			}

			auto splitArgs = core::utils::tokenise(args, ' ');
			if (splitArgs.size() == 0) {
				std::cout << "Please select a type of visual." << std::endl;
			}

			if (splitArgs[0] == "candles") {
				initscr();
				visuals::candlesticks(env);
				core::utils::leaveScrOnInput();
				return true;
			}
			if (splitArgs[0] == "plot") {
				initscr();
				visuals::plot(env);
				core::utils::leaveScrOnInput();
				return true;
			}
			if (splitArgs[0] == "prediction") {
				int predictionCount = 
					splitArgs.size() == 2 ? std::stoi(splitArgs[1]) : 12;

				initscr();
				visuals::prediction(env, predictionCount);
				core::utils::leaveScrOnInput();
				return true;
			}
			if (splitArgs[0] == "temp") {
				visuals::temp(env);
				return true;
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
