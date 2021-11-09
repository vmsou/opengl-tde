#pragma once
#include <vector>

#include "v3f.hpp"
#include "c4f.hpp"
#include "Object/PooledObject3D.hpp"
#ifndef DISC_OBJ_HPP
#define DISC_OBJ_HPP

class Disc : public PooledObject3D<Disc> {
public:
	// Attributes
	int sides;
	double radius;
	c4f c2;
	int dir = 1;

	// Constructors
	Disc() = default;
	Disc(const DisplayFile& df);
	Disc(int sides, double radius, const v3f& pos, const c4f& c1, int dir);
	Disc(int sides, double radius, const v3f& pos, const c4f& c1, const c4f& c2, int dir);

	// Methods
	void draw() const override;
};

#endif