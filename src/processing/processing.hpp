#pragma once

#include <vector>
#include "../models/models.hpp"

namespace processing {

std::vector<float> predictSeasonal(const std::vector<float>& data, int seasonLength, int recentLength, int predictionCount);

} // namespace processing
