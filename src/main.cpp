#include <iostream>

#include "core/Environment.hpp"
#include "models/TempTimeline.hpp"
#include "parsing/datasetLoader.hpp"

int main(){
	
	core::Store store {};
	core::Interface interface {};
	core::Environment env { store, interface };

	env.interface.registerCommand("echo", [](const std::string& args) {
		std::cout << args << std::endl;
	});

	env.interface.registerCommand("list-country", [&env](const std::string&) {
			for (auto timeline: env.store.getAll<models::TempTimeline>()) {
				std::cout << timeline.countryCode << std::endl;
			}
	});

	env.interface.registerCommand("load", [&env](const std::string& args) {
		parsing::loadDataset(args, env);
	});


	while (true) {
		env.interface.run("> ");
	}

	return 0;
}
