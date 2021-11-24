#pragma once
#include <vector>
#include "v3f.hpp"
#include "c4f.hpp"
#include "Object/PooledObject3D.hpp"
#include "Disc.hpp"
#ifndef CYLINDER_OBJ_HPP
#define CYLINDER_OBJ_HPP

class Cylinder : public PooledObject3D<Cylinder> {
private:
	// Attributes
	double size;
	int sides, sections;
	double radius;
	Disc d1, d2;

public:
	// Constructors
	Cylinder(const DisplayFile& df);
	Cylinder(double size, int sides, int sections, double radius, const v3f& pos, const c4f& c1);

	// Methods
	const char* name() const override { return "Cilindro"; }
	void draw() const override;
	void update(const OBJ_MODIFIERS& mdf) override { 
		this->modifiers = mdf; d1.update(modifiers); d2.update(modifiers); 
		d1.pos = pos; d2.pos = pos + v3f{ 0, 0, float(size) };
	}
};

#endif
