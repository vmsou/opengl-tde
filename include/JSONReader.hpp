#pragma once
#include <unordered_map>
#include <iostream>
#include <sstream>
#ifndef JSON_READER_HPP
#define JSON_READER_HPP

// Exceptions
struct BadJSONPair : std::exception {};
struct BadJSONObject : std::exception {};
struct JSONKeyNotFound : std::exception {};
struct BadJSONConvert : std::exception {};

struct JSONPair {
	// Attributes
	std::string key;
	std::string value;

};

// Stream operators
std::istream& operator>>(std::istream& is, JSONPair& pair);

struct JSONObject {
	// Attributes
	std::unordered_map<std::string, std::string> map;

	// Methods
	bool has(const std::string& key) const;

	template <typename T>
	T get(const std::string& key) const {
		if (!has(key)) throw JSONKeyNotFound{};
		std::istringstream iss{ map.at(key) };
		T converted;
		if (!(iss >> converted)) throw BadJSONConvert{};

		return converted;
	}

	// Access operators
	std::string& operator[](const std::string& key) { return map.at(key); }
	std::string operator[](const std::string& key) const { return map.at(key); }
};

// Stream operators
std::istream& operator>>(std::istream& is, JSONObject& obj);
std::ostream& operator<<(std::ostream& os, const JSONObject& obj);


// Helper functions
template <typename T>
std::string to_string(const T& val);

#endif
