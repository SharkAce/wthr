#pragma once

#include <unordered_map>
#include <string>
#include <any>

namespace core {

class Store {

// Based on info I got from https://cengizhanvarli.medium.com/what-is-std-any-in-c-76f2575ad37b combined with prior knowlede of templates

public:
	template <typename T>
	void add(const std::string& id, T value) {
		data[id] = std::any(value);
	}

	template <typename T>
	T& get(const std::string& id) {
		return std::any_cast<T&>(data[id]);
	}

private:
	std::unordered_map<std::string, std::any> data;
};

} // namespace core
