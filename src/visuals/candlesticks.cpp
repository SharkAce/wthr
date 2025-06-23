#include <cmath>
#include "visuals.hpp"
#include "../models/models.hpp"

using models::Candlestick;

void visuals::candlesticks(const core::Environment& env) {
	auto& s = env.store
		.get<models::DataScopeState&>("dataScopeState");

	auto& t = env.store
		.get<models::TimelineMap&>("timelines")
		.at(s.countryCode);

	int start, end, padding;
	
	short segmentId;
	std::vector<float> segmentValues;
	std::vector<Candlestick> candles;

	switch(s.scopeLevel) {
		case models::DataScope::Country:
			start = t.yearlyReadings.begin()->first.year;
			end = t.yearlyReadings.rbegin()->first.year;
			padding = 14;

			segmentId = start;
			for (auto& [ts, reading]: t.dailyReadings) {
				if (segmentId != ts.year) {
					candles.push_back(Candlestick(segmentValues));
					segmentValues.clear();
					++segmentId;
				}
				segmentValues.push_back(reading);
			};
			break;

		case models::DataScope::Year:
			start = 1;
			end = 12;
			padding = 5;

			segmentId = start;
			for (auto& [ts, reading]: t.dailyReadings) {
				if (ts.year != s.timeData.year) continue;
				if (segmentId != ts.month) {
					candles.push_back(Candlestick(segmentValues));
					segmentValues.clear();
					++segmentId;
				}
				segmentValues.push_back(reading);
			};
			break;

		case models::DataScope::Month:
			start = 1;
			end = 28;
			padding = 2;

			segmentId = start;
			for (auto& [ts, reading]: t.hourlyReadings) {
				if (
					ts.year != s.timeData.year || 
					ts.month != s.timeData.month
				) continue;
				if (ts.day > end) end = ts.day;

				if (segmentId != ts.day) {
					candles.push_back(Candlestick(segmentValues));
					segmentValues.clear();
					++segmentId;
				}
				segmentValues.push_back(reading);
			}
			break;

		default:
			return;
	}

	// Adding the last segment
	if (!segmentValues.empty()) {
		candles.push_back(Candlestick(segmentValues));
	}
	
	float minValue = candles.at(0).low;
	float maxValue = candles.at(0).high;
	for (const auto& candle: candles) {
		if (candle.low < minValue) minValue = candle.low;
		if (candle.high > maxValue) maxValue = candle.high;
	}
	minValue -= padding;
	maxValue += padding;
	float valueRange = maxValue - minValue;

	graph(start, end, (int)minValue, (int)maxValue);

	float spacing = (float)cols / (float)candles.size();
	unsigned int i = 0;

	for (const auto& candle: candles) {
		int col = offsetX + 1 + std::floor((float)i * spacing + spacing / 2);

		Candlestick normalized {
			(candle.open - minValue) / valueRange * rows,
			(candle.high - minValue) / valueRange * rows,
			(candle.low - minValue) / valueRange * rows,
			(candle.close - minValue) / valueRange * rows
		};

		int rowLow = std::floor(rows - normalized.low + offsetY);
		int rowHigh = std::ceil(rows - normalized.high + offsetY);

		move(rowHigh, col);
		vline('|', rowLow - rowHigh);

		int rowOpen = std::round(rows - normalized.open + offsetY);
		int rowClose = std::round(rows - normalized.close + offsetY);

		// Comparison is reversed because of top to bottom render
		int rowTop = std::min(rowOpen, rowClose);
		int rowBottom = std::max(rowOpen, rowClose);

		char bodyChar;
		if (rowOpen > rowClose) bodyChar = '+';
		if (rowOpen < rowClose) bodyChar = '-';
		if (rowOpen == rowClose) bodyChar = '=';

		move(rowTop, col);
		vline(bodyChar, rowBottom - rowTop + 1);

		++i;
	}
}

