#pragma once
#include "v3f.hpp"
#include "c4f.hpp"
#include "Object/PooledObject3D.hpp"
#ifndef CUBE_OBJ_HPP
#define CUBE_OBJ_HPP

class Cube : public PooledObject3D<Cube> {
private:
	// Attributes
	float size;

public:
	// Constructors
	Cube(float size, const v3f& pos, const c4f& c1);
	Cube(const DisplayFile& df);

	// Methods
	void draw() const override;

	template <size_t Length>
	v3f middlePoint(const v3f(&vs)[Length]) const;

	template <size_t Length>
	void addVertices(const v3f* (&face)[Length]) const;
};

#endif