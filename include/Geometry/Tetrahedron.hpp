#pragma once
#include "v3f.hpp"
#include "c4f.hpp"
#include "Object/PooledObject3D.hpp"
#ifndef TETRAHEDRON_OBJ_HPP
#define TETRAHEDRON_OBJ_HPP

class Tetrahedron : public PooledObject3D<Tetrahedron> {
private:
	// Attributes
	float size;
	c4f c1;
	int angle = 0;

public:
	// Constructors
	Tetrahedron(float size, const v3f& pos, const c4f& c1);

	// Methods
	void draw() const override;

	template <size_t Length>
	void addVertices(const v3f* (&face)[Length]) const;
};

#endif
