#pragma once

#include <string>
#include <vector>

namespace core::utils {

std::vector<std::string> tokenise(const std::string& csvLine, char separator);

} // namespace core::utils
