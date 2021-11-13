#pragma once
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <functional>
#ifndef JSON_READER_HPP
#define JSON_READER_HPP

// Exceptions
struct BadJSONPair : std::exception {};
struct BadJSONObject : std::exception {};
struct JSONKeyNotFound : std::exception {};
struct BadJSONConvert : std::exception {};

enum class JSONType {
	INVALID,
	STRING,
	NUMBER
};


struct JSONElement {
	// Attributes
	JSONType type;
	std::string value;

	bool operator==(const std::string& other) const { return value == other; }
	bool operator==(const JSONElement& other) const { return value == other.value; }
};

std::istream& operator>>(std::istream& is, JSONElement& element);
std::ostream& operator<<(std::ostream& os, const JSONElement& element);

struct JSONPair {
	// Attributes
	JSONElement key;
	JSONElement value;

};

// Stream operators
std::istream& operator>>(std::istream& is, JSONPair& pair);

namespace std {
	template <>
	struct hash<JSONElement> {
		size_t operator()(const JSONElement& element) const {
			return hash<string>()(element.value);
		}
	};
}

struct JSONObject {
	// Attributes
	std::unordered_map<JSONElement, JSONElement> map;

	// Methods
	bool has(const std::string& key) const;

	template <typename T>
	T get(const std::string& key) const {
		const JSONElement e{ JSONType::STRING, key };	// bad, fix this later
		if (!has(key)) throw JSONKeyNotFound{};
		std::istringstream iss{ map.at(e).value };
		T converted;
		if (!(iss >> converted)) throw BadJSONConvert{};

		return converted;
	}
};

// Stream operators
std::istream& operator>>(std::istream& is, JSONObject& obj);
std::ostream& operator<<(std::ostream& os, const JSONObject& obj);


// Helper functions
template <typename T>
std::string to_string(const T& val);

#endif
