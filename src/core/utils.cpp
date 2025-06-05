#include "utils.hpp"

namespace core::utils {

std::vector<std::string> tokenise(const std::string& csvLine, char separator) {
	std::vector<std::string> tokens;
	size_t start = 0;
	size_t end = 0;

	while (start < csvLine.length()) {
		end = csvLine.find(separator, start);

		if (end == std::string::npos) {
			tokens.push_back(csvLine.substr(start));
			break;
		} else {
			tokens.push_back(csvLine.substr(start, end - start));
			start = end + 1;
		}
	}

	if (!csvLine.empty() && csvLine.back() == separator) {
		tokens.push_back("");
	}

	return tokens;
}

} // namespace core::utils
