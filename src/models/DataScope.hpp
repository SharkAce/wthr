#pragma once

#include <string>
#include "Timestamp.hpp"

namespace models {

enum class DataScope {
	Unset = 0,
	Country,
	Year,
	Month,
	Day,
	Hour
};

struct DataScopeState {
	DataScope scopeLevel { 0 };
	std::string countryCode { "" };
	timestamp::Hour timeData { 0, 0, 0, 0 };
};

}
