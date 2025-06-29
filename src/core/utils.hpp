#pragma once

#include <string>
#include <vector>
#include <map>

namespace core::utils {

std::vector<std::string> tokenise(const std::string& line, char separator);

float average(const std::vector<float>&);
float min(const std::vector<float>&);
float max(const std::vector<float>&);

int getDaysInMonth(int year, int month);

template <typename K, typename M>
bool validateKey(const K& key, const M& container) {
	return container.find(key) != container.end();
};

template <typename K, typename V>
std::vector<V> getRange(const K& startKey, const K& endKey, const std::map<K,V>& m) {
	auto start = m.lower_bound(startKey);
	auto end = m.upper_bound(endKey);

	std::vector<V> values;
	for (auto it = start; it != end; ++it) {
		values.push_back(it->second);
	}
	return values;
}

template <typename V>
std::vector<V> getRange(size_t start, size_t end, const std::vector<V>& vec) {
	if (start< 0) start = 0;
	if (end > vec.size()) end = vec.size();

	return std::vector<V>(vec.begin() + start, vec.begin() + end);
}

void leaveScrOnInput();

} // namespace core::utils
