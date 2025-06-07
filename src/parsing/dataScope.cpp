#include "parsing.hpp"

namespace parsing {

models::DataScope readDataScope(const std::string& scope) {
	if (scope == "country") return models::DataScope::Country;
	if (scope == "year") return models::DataScope::Year;
	if (scope == "month") return models::DataScope::Month;
	if (scope == "day") return models::DataScope::Day;
	if (scope == "hour") return models::DataScope::Hour;
	return models::DataScope::Unset;
}

} // namespace parsing
