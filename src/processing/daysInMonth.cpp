#include <chrono>

namespace processing {

int daysInMonth(int y, int m) {
	return unsigned{ (std::chrono::last/m/y).day() };
}

} // namespace processing
