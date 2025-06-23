#include <ncurses.h>
#include <limits>
#include <chrono>

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

float min(const std::vector<float>& numbers) {
	float min = std::numeric_limits<float>::max();
	for (const auto& number: numbers) {
		if (number < min) min = number;
	}
	return min;
}

float max(const std::vector<float>& numbers) {
	float max = std::numeric_limits<float>::min();
	for (const auto& number: numbers) {
		if (number > max) max = number;
	}
	return max;
}

void leaveScrOnInput() {
	getch();
	endwin();
	clear();
}

// Copied from https://stackoverflow.com/a/79232587
int getDaysInMonth(int year, int month) {
	return unsigned{ (std::chrono::last/month/year).day() };
}

} // namespace core::utils
