#include <ncurses.h>

#include "../core/Environment.hpp"
#include "../models/models.hpp"
#include "../visuals/visuals.hpp"

namespace commands {

void registerShow(core::Environment& env) {
	core::Interface::Command show {
		[&env](const std::string& arg) {
			if (arg == "canddles") {
				initscr();
				core::utils::leaveScrOnInput();
				return true;
			}
			if (arg == "plot") {
				initscr();
				visuals::plot(env);
				core::utils::leaveScrOnInput();
				return true;
			}
			if (arg == "prediciton") {
				initscr();
				core::utils::leaveScrOnInput();
				return true;
			}
			if (arg == "temp") {
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
