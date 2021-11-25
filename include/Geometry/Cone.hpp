#pragma once
#include "v3f.hpp"
#include "c4f.hpp"
#include "Object/PooledObject3D.hpp"
#include "Disc.hpp"
#ifndef CONE_OBJ_CPP
#define CONE_OBJ_CPP

class Cone : public PooledObject3D<Cone> {
private:
	// Attributes
	int sides;
	double radius;
	double height;
	c4f c2;
	Disc base;

public:
	// Constructors
	Cone(const DisplayFile& df);
	Cone(double height, int sides, double radius, v3f pos, c4f c1);
	Cone(double height, int sides, double radius, v3f pos, c4f c1, c4f c2);

	// Methods
	const char* name() const override { return "Cone"; }
	void draw() const override;
	void update(const OBJ_MODIFIERS& mdf) override { PooledObject3D::update(mdf); base.update(mdf); base.pos = pos; }
};

#endif
