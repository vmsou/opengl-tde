#pragma once
#include "DisplayReader.hpp"
#ifndef DSP_READER_CPP
#define DSP_READER_CPP

// File
std::ostream& operator<<(std::ostream& os, const DisplayFile& dd) {
	return os << "{ " << dd.type << " " << dd.pos << " " << dd.color << " " << dd.data << "}";
}

std::istream& operator>>(std::istream& is, DisplayFile& dd) {
	char ch1;
	int type;
	v3f pos;
	c4f color;
	JSONObject data;

	is >> ch1;

	if (ch1 != '{') {
		std::cout << "Expected '{' got '" << ch1 << "'\n";
		is.setstate(std::ios_base::failbit);
		return is;
	}

	is >> type >> pos >> color >> data;

	dd = { type, pos, color, data };

	is >> ch1;

	if (ch1 != '}') {
		std::cout << "Expected '{' got '" << ch1 << "'\n";
		is.setstate(std::ios_base::failbit);
	}
	return is;
}

// Array
DisplayArray::DisplayArray(const char* filename) {
	std::ifstream ifs(filename);
	if (!ifs) std::cout << "Couldn't open " << filename << '\n';
	else ifs >> *this;
}

std::ostream& operator<<(std::ostream& os, const DisplayArray& dArr) {
	os << "[\n";
	for (const DisplayFile& df : dArr) os << " " << df << "\n";
	return os << "]";
}

std::istream& operator>>(std::istream& is, DisplayArray& dArr) {
	char ch1;

	if (is >> ch1 && ch1 == '[') {
		while (is >> ch1 && ch1 == '{') {
			is.putback(ch1);
			DisplayFile df;
			is >> df;
			dArr.files.emplace_back(std::move(df));
		}
		is >> ch1;
		if (ch1 != ']') std::cout << "Expected ']' got " << ch1 << '\n';
		return is;
	}

	is.setstate(std::ios_base::failbit);

	return is;
}

#endif