#pragma once
#include "v3f.hpp"

class Viewport {
public:
	// Attributes
	v3f min, max;

	// Methods
	float fSx(Viewport other) {
		return (max.x - min.x) / (other.max.x - other.min.x);
	}
	float fSy(Viewport other) {
		return (max.y - min.y) / (other.max.y - other.min.y);
	}
	float XS(Viewport other, float XW) {
		return fSx(other) * (XW - other.min.x) + min.x;
	}
	float YS(Viewport other, float YW) {
		return fSy(other) * (YW - other.min.y) + min.y;
	}
};