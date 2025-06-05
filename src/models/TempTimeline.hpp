#pragma once

#include <vector>
#include "../core/Environment.hpp"

namespace models {

struct Timestamp {
	short year;
	unsigned short month;
	unsigned short day;
	unsigned short hour;
};

struct TempReading {
	Timestamp timestamp;
	float temp;
};

struct TempTimeline {
	std::string countryCode;
	std::vector<TempReading> timeline;
};

} // namespace models
