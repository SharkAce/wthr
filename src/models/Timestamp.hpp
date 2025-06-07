#pragma once

namespace models::timestamp {

struct Hour {
	short year;
	unsigned short month;
	unsigned short day;
	unsigned short hour;

	// Overloading comparasion operator to keep order when used as key to a map
	bool operator<(const Hour& other) const {
		if (year != other.year) return year < other.year;
		if (month != other.month) return month < other.month;
		if (month != other.day) return day < other.day;
		return hour < other.hour;
	}
};

struct Day {
	short year;
	unsigned short month;
	unsigned short day;

	bool operator<(const Day& other) const {
		if (year != other.year) return year < other.year;
		if (month != other.month) return month < other.month;
		return day < other.day;
	}
};

struct Month {
	short year;
	unsigned short month;

	bool operator<(const Month& other) const {
		if (year != other.year) return year < other.year;
		return month < other.month;
	}
};

struct Year {
	short year;

	bool operator<(const Year& other) const {
		return year < other.year;
	}
};

} // namespace models::timestamp
