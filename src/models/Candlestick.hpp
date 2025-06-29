#pragma once

#include <vector>

#include "../core/utils.hpp"

namespace models {

struct Candlestick {
	Candlestick(const std::vector<float>& data):
	open(data.front()),
	high(core::utils::max(data)),
	low(core::utils::min(data)),
	close(data.back()) {};

	Candlestick(float open, float high, float low, float close):
	open(open),
	high(high),
	low(low),
	close(close) {};

	float open;
	float high;
	float low;
	float close;
};

} // namespace models
