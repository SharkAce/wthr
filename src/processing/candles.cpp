#include <cmath>
#include "processing.hpp"

namespace processing {

std::vector<Candlestick> computeCandles(const std::vector<float>& data, int candleSize) {

	if (data.empty() || candleSize <= 0) return {};

	
	std::vector<Candlestick> candles;
	for (size_t i = 0; i < data.size() - candleSize; i += candleSize) {
		auto chunk = core::utils::getRange(i, i + candleSize, data);
		candles.emplace_back(chunk);
	}

	return candles;
}

} // namespace processing
