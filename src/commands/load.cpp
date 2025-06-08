#include "../core/Environment.hpp"
#include "../parsing/parsing.hpp"
#include "../models/TempTimeline.hpp"
#include <filesystem>

namespace commands {

void registerLoad(core::Environment& env) {
	core::Interface::Command load {
		[&env](const std::string& arg) {

			std::string fileName = arg;
			
			// If no arg is given use the first file
			if (arg.empty()) {
				for (const auto& entry : std::filesystem::directory_iterator("datasets/")) {
					auto filePath = entry.path().string();
					fileName = filePath.substr(filePath.find('/') + 1);
					break;
				}
			}

			if (!parsing::loadDataset("datasets/" + fileName, env)) {
				std::cout << "Encoutered an error while loading the dataset." << std::endl;
				return false;
			}
			std::cout << "Loaded " 
								<< env.store.get<models::TimelineMap>("timelines").begin()->second.hourlyReadings.size() 
								<< " data points" << std::endl;
			return true;
		},
		[]() {
			std::cout << "[load]\nUsed to load a dataset inside the datasets directory.\n" 
								<< "Usage: load <file name>\n"
								<< "The available datasets are:" << std::endl;

			for (const auto& entry : std::filesystem::directory_iterator("datasets/")) {
				auto filePath = entry.path().string();
				std::cout << filePath.substr(filePath.find('/') + 1) << std::endl;
			}
		}
	};

	env.interface.registerCommand("load", load);
}

} //namespace commands
