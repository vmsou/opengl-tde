#pragma once
#include <iostream>
#include <vector>
#include <fstream>

#include "JSONReader.hpp"
#include "v3f.hpp"
#ifndef DSP_READER_HPP
#define DSP_READER_HPP

enum class OBJ_TYPE {
	None = 0,
	Disc,
	Cone,
	Cube,
	Cylinder,
	Tetrahedron
};


struct DisplayFile {
	int type;
	v3f pos;
	c4f color;
	JSONObject data;
};

std::ostream& operator<<(std::ostream& os, const DisplayFile& dd);
std::istream& operator>>(std::istream& is, DisplayFile& dd);


struct DisplayArray {
	// Attributes
	std::vector<DisplayFile> files;
	using DisplayIter = std::vector<DisplayFile>::const_iterator;

	// Constructors
	DisplayArray(const char* filename);

	// Methods
	DisplayIter begin() const { return files.begin(); }
	DisplayIter end() const { return files.end(); }

};

std::istream& operator>>(std::istream& is, DisplayArray& dArr);
std::ostream& operator<<(std::ostream& os, const DisplayArray& dArr);

#endif