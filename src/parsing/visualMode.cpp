#include "parsing.hpp"

namespace parsing {

models::VisualMode readVisualMode(const std::string& mode) {
	if (mode == "temp") return models::VisualMode::temp;
	if (mode == "plot") return models::VisualMode::plot;
	if (mode == "prediction") return models::VisualMode::prediction;
	if (mode == "candles") return models::VisualMode::candlestick;
	return models::VisualMode::invalid;
}

} // namespace parsing
