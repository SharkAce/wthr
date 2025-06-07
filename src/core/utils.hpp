#pragma once

#include <string>
#include <vector>

namespace core::utils {

std::vector<std::string> tokenise(const std::string& line, char separator);

float average(const std::vector<float>&);

template <typename K, typename M>
bool validateKey(const K& key, const M& container) {
	return container.find(key) != container.end();
};

} // namespace core::utils
