#include "datasetLoader.hpp"
#include <fstream>

namespace parsing {

void loadDataset(const std::string& filePath, core::Environment& env) {
	//if (!validator(filePath, env)) return;

	std::ifstream fileHandle { filePath };
	std::string fieldsText;

	std::getline(fileHandle, fieldsText);
	auto fieldsList = core::utils::tokenise(fieldsText, ',');

	std::vector<models::TempTimeline> timelines;
	for (unsigned int i = 1; i < fieldsList.size(); ++i) {
		timelines.push_back(models::TempTimeline {  
			fieldsList[i].substr(0,2),
			std::vector<models::TempReading>{}
		});
	}

	std::string row;
	while (std::getline(fileHandle, row)) {
		auto rowData = core::utils::tokenise(row, ',');
		for (unsigned int i = 1; i < rowData.size(); ++i) {
			timelines[i-1].timeline.push_back(models::TempReading{
				readTimestamp(rowData[0]),
				std::stof(rowData[i]),
			});
		}
	}

	for (auto& timeline: timelines) {
		env.store.add(timeline.countryCode + "_timeline", timeline);
	}
};

models::Timestamp readTimestamp(const std::string& s) {
	std::string date = s.substr(0,s.find('T'));
	std::string hour = s.substr(s.find('T')+1, 2);
	auto dateData = core::utils::tokenise(date, '-');
	return models::Timestamp { 
		(short) std::stoi(dateData[0]),
		(unsigned short) std::stoi(dateData[1]),
		(unsigned short) std::stoi(dateData[2]),
		(unsigned short) std::stoi(hour)
	};
};

} // namespace parsing
