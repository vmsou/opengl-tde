#pragma once
#include "JSONReader.hpp"
#ifndef JSON_READER_CPP
#define JSON_READER_CPP

// JSONPair
// Stream operators
std::istream& operator>>(std::istream& is, JSONPair& pair) {
	char ch1;
	is >> ch1;
	if (ch1 != '\"') throw BadJSONPair{};

	// Read Key
	std::string k;
	while (is >> ch1 && ch1 != '\"') k += ch1;
	if (ch1 != '\"') throw BadJSONPair{};

	// Close Quote + Equals
	is >> ch1;
	if (ch1 != ':') throw BadJSONPair{};

	std::string v;		// Read String
	is >> ch1;
	if (ch1 == '\"') {
		while (is >> ch1 && ch1 != '\"') v += ch1;
		if (ch1 != '\"') throw BadJSONPair{};
	} else {			// Read value
		is.putback(ch1);
		float f;
		is >> f;
		v = to_string(f);
	}

	pair = { k, v };

	return is;
}

// JSONObject
// Methods
bool JSONObject::has(const std::string& key) const { 
	return map.find(key) != map.end(); 
}

// Stream operators
std::istream& operator>>(std::istream& is, JSONObject& obj) {
	char ch1;
	is >> ch1;
	if (ch1 != '{') throw BadJSONObject{};

	while (is >> ch1 && ch1 == '\"') {
		is.putback(ch1);
		JSONPair pair;
		is >> pair;
		obj.map[pair.key] = pair.value;

		is >> ch1;
		if (ch1 != ',') is.putback(ch1);
	}

	return is;
}

std::ostream& operator<<(std::ostream& os, const JSONObject& obj) {
	os << "{ ";
	const size_t len = obj.map.size();
	size_t i = 0;
	for (const auto& kp : obj.map) {
		os << "\"" << kp.first << ": " << "\"" << kp.second << "\"";
		++i;
		if (i < len) os << ", ";
	}

	return os << " }";
}

template <typename T>
std::string to_string(const T& val) {
	std::ostringstream oss;
	oss << val;
	return oss.str();
}

#endif
