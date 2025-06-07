#include "utils.hpp"

namespace core::utils {

std::vector<std::string> tokenise(const std::string& line, char separator) {
	std::vector<std::string> tokens;
	size_t start = 0;
	size_t end = 0;

	while (start < line.length()) {
		end = line.find(separator, start);

		if (end == std::string::npos) {
			tokens.push_back(line.substr(start));
			break;
		} else {
			tokens.push_back(line.substr(start, end - start));
			start = end + 1;
		}
	}

	if (!line.empty() && line.back() == separator) {
		tokens.push_back("");
	}

	return tokens;
}

float average(const std::vector<float>& numbers) {
	float total = 0.f;
	for (auto number: numbers) total += number;
	return total / numbers.size();
}

} // namespace core::utils
