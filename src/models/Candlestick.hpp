#pragma once

#include <vector>

#include "../core/utils.hpp"

namespace models {

struct Candlestick {
	Candlestick(std::vector<float> data):
	open(data.front()),
	high(core::utils::max(data)),
	low(core::utils::min(data)),
	close(data.back()) {};

	float open;
	float high;
	float low;
	float close;
};

}
