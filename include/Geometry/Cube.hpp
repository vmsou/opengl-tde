#pragma once
#include "v3f.hpp"
#include "c4f.hpp"
#include "Object/PooledObject3D.hpp"
#ifndef CUBE_OBJ_HPP
#define CUBE_OBJ_HPP

class Cube : public PooledObject3D<Cube> {
private:
	// Attributes
	float a;
	c4f c1;
public:
	// Constructors
	Cube(float a, v3f pos, c4f c1);

	// Methods
	void draw() const override;

	template <size_t Length>
	v3f middlePoint(const v3f(&vs)[Length]) const;

	template <size_t Length>
	void addVertices(const v3f* (&face)[Length]) const;
};

#endif