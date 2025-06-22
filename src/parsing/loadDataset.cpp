#include "parsing.hpp"
#include <fstream>
#include <map>


namespace parsing {

bool loadDataset(const std::string& filePath, core::Environment& env) {
	//if (!validator(filePath, env)) return false;

	std::ifstream fileHandle { filePath };
	std::string fieldsText;

	if (!fileHandle.is_open()) return false;

	std::getline(fileHandle, fieldsText);
	auto fieldsList = core::utils::tokenise(fieldsText, ',');
	auto countryCodes = fieldsList;

	// remove the utc field
	countryCodes.erase(countryCodes.begin());
	int dataSize = countryCodes.size();
	std::vector<models::HourlyReadings> data(
		dataSize, models::HourlyReadings{}
	);

	std::string row;
	while (std::getline(fileHandle, row)) {
		auto rowData = core::utils::tokenise(row, ',');
		models::timestamp::Hour ts = readTimestamp(rowData[0]);

		for (unsigned int i = 1; i < rowData.size(); ++i) {
			data[i-1][ts] = std::stof(rowData[i]);
		}
	}

	auto& timelines = env.store.get<models::TimelineMap&>("timelines");
	for (int i = 0; i < dataSize; ++i) {
		auto code = countryCodes[i].substr(0,2);
		models::TempTimeline timeline(code, data[i]);
		timelines.insert_or_assign(code, timeline);
	}

	fileHandle.close();
	return true;
};

models::timestamp::Hour readTimestamp(const std::string& s) {
	std::string date = s.substr(0,s.find('T'));
	std::string hour = s.substr(s.find('T')+1, 2);
	auto dateData = core::utils::tokenise(date, '-');
	return models::timestamp::Hour { 
		(short) std::stoi(dateData[0]),
		(unsigned short) std::stoi(dateData[1]),
		(unsigned short) std::stoi(dateData[2]),
		(unsigned short) std::stoi(hour)
	};
};

} // namespace parsing
