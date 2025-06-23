#include "processing.hpp"

std::vector<float> processing::predictSeasonal(const std::vector<float>& data, int seasonLength, int recentLength, int predictionCount) {
	std::vector<float> seasonalSum(seasonLength, 0.f);
	std::vector<int> seasonalCount(seasonLength, 0);

	for (unsigned int i = 0; i < data.size(); ++i) {
		int seasonalIndex = i % seasonLength;

		seasonalSum[seasonalIndex] += data[i];
		seasonalCount[seasonalIndex] ++;
	}

	std::vector<float> seasonalAverage;
	for (int i = 0; i < seasonLength; ++i) {
		if (seasonalCount[i] > 0) {
			seasonalAverage.push_back(seasonalSum[i]/seasonalCount[i]);
		}
	}

	float recentDeviationSum = 0;
	if ((unsigned long) recentLength > data.size()) recentLength = data.size();

	for (int i = (int)data.size() - recentLength; i < (int)data.size(); ++i) {
		recentDeviationSum += data[i] - seasonalAverage[i % seasonLength];
	}
	float recentDeviation = recentDeviationSum / recentLength;

	std::vector<float> predictions;
	for (int i = 0; i < predictionCount; ++i) {
		int seasonalIndex = (data.size() + i) % seasonLength;
		
		predictions.push_back(seasonalAverage[seasonalIndex] + recentDeviation);
	}
	return predictions;
}
