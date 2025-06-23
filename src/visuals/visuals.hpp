#pragma once

#include <ncurses.h>
#include "../core/Environment.hpp"

namespace visuals {

void graph(int startX, int endX, int startY, int endY);

void plot(const core::Environment&);
void candlesticks(const core::Environment&);
void prediction(const core::Environment&, int predictionCount);
void temp(const core::Environment&);

const int rows = 16;
const int cols = 61;
const int offsetX = 10;
const int offsetY = 5;

} // namespace visuals
