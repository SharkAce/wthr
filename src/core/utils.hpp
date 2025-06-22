#pragma once

#include <string>
#include <vector>
#include <map>

namespace core::utils {

std::vector<std::string> tokenise(const std::string& line, char separator);

float average(const std::vector<float>&);
float min(const std::vector<float>&);
float max(const std::vector<float>&);

template <typename K, typename M>
bool validateKey(const K& key, const M& container) {
	return container.find(key) != container.end();
};

template <typename K, typename V>
std::vector<V> getRange(K& startKey, K& endKey, std::map<K,V> m) {
	auto start = m.find(startKey);
	auto end = m.find(endKey);

	std::vector<V> values;
	for (auto i = start; i <= end; ++i) {
		values.push_back(m.at(i));
	}
	return values;
}

void leaveScrOnInput();

} // namespace core::utils
