#pragma once

#include <unordered_map>
#include <string>
#include <any>
#include <vector>
#include <optional>

#include "utils.hpp"

namespace core {

class Store {

public:
	template <typename T>
	void add(const std::string& id, T value) {
		data[id] = std::any(value);
	}

	template <typename T>
	T get(const std::string& id) {
		return std::any_cast<T>(data[id]);
	}

	template <typename T>
	std::vector<T> getAll() {
		std::vector<T> results;
		for (const auto& [key, value] : data) {
			if (value.type() == typeid(T)) {
				results.push_back(std::any_cast<T>(value));
			}
		}
		return results;
	}

private:
	std::unordered_map<std::string, std::any> data;
};

} // namespace core
