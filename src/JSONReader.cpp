#pragma once
#include "JSONReader.hpp"
#ifndef JSON_READER_CPP
#define JSON_READER_CPP

// JSONElement
// Stream operators
std::istream& operator>>(std::istream& is, JSONElement& element) {
	char ch1;
	is >> ch1;

	JSONType type;
	std::string value;

	if (ch1 == '\"') {									// Quote Start
		while (is >> ch1 && ch1 != '\"') value += ch1;
		if (ch1 != '\"') throw BadJSONPair{};			// Quote End
		type = JSONType::STRING;
	} else {											// Number Start
		is.putback(ch1);
		double d;
		is >> d;
		value = to_string(d);
		type = JSONType::NUMBER;
	}													// Number End

	element = { std::move(type), std::move(value) };
	return is;
}

std::ostream& operator<<(std::ostream& os, const JSONElement& element) {
	if (element.type == JSONType::STRING) return os << '\"' << element.value << '\"';
	else if (element.type == JSONType::NUMBER) return os << element.value;
	return os << element.value;
}

// JSONPair
// Stream operators
std::istream& operator>>(std::istream& is, JSONPair& pair) {
	char ch1;

	JSONElement key, value;
	is >> key >> ch1 >> value;
	if (ch1 != ':') throw BadJSONPair{};

	pair = { std::move(key), std::move(value) };

	return is;
}

// JSONObject
// Methods
bool JSONObject::has(const std::string& key) const { 
	const JSONElement e{ JSONType::STRING, key };		// bad, fix this later
	return map.find(e) != map.end(); 
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
		os << kp.first << ": " << kp.second;
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
