#pragma once

#include <vector>
#include "../models/models.hpp"

namespace processing {

using models::Candlestick;

std::vector<float> predictSeasonal(const std::vector<float>& data, int seasonLength, int recentLength, int predictionCount);
std::vector<Candlestick> computeCandles(const std::vector<float>& data, int candleSize);

} // namespace processing
