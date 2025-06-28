#include "visuals.hpp"
#include <string>
#include <iomanip>

void visuals::graph(int startX, int endX, int startY, int endY) {
	move(offsetY,offsetX);
	vline('|',rows);
	move(offsetY+rows,offsetX+1);
	hline('-',cols);

	// Draw the vertical labels
	const int vLabels = 6;
	const float vValueInterval = (double)(endY - startY) / (vLabels - 1);
	const int vCharInterval = (rows - 1) / (vLabels - 1);
	for (int i = 0; i < vLabels; ++i) {
		float value = (float)startY + vValueInterval*(float)i;
		std::string textValue;
		std::stringstream ss;

		if (endY - startY >= rows) {
			ss << std::fixed << std::setprecision(0) << value << "C";
		} else {
			ss << std::fixed << std::setprecision(2) << value << "C";
		}
		textValue = ss.str();
		move(rows + offsetY - (i*vCharInterval) - 1, offsetX - textValue.size());
		printw("%s", textValue.c_str());
	}

	// Draw the horizontal labels
	int hLabels, hCharInterval, localOffsetX;
	float hValueInterval;
 	int hLabelSize = std::to_string(endX).size();
	// Change how many labels are shown depending on the size of the last label
	if (hLabelSize >= 3) {
		hLabels = 7;
		hValueInterval = (double)(endX - startX) / (hLabels - 1);
		hCharInterval = (cols / hLabels) + 1;
		localOffsetX = offsetX + (hCharInterval/2) - 2;
	} else {
		hLabels = 12;
		hValueInterval = (double)(endX - startX) / (hLabels - 1);
		hCharInterval = cols / hLabels;
		localOffsetX = offsetX + (hCharInterval/2) + 1;
	}

	for (int i = 0; i < hLabels; ++i) {
		int value = startX + hValueInterval*(float)i;
		auto stringValue = std::to_string(value);
		move(rows + offsetY + 1, localOffsetX + (i*hCharInterval));
		printw("%s", stringValue.c_str());
	}
};
