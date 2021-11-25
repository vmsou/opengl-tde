#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <memory>
#include <vector>

#include "v3f.hpp"
#include "c4f.hpp"
#include "DisplayReader.hpp"
#ifndef OBJ_3D_HPP
#define OBJ_3D_HPP

struct OBJ_MODIFIERS {
	bool grid_enabled = true;
	int angleY = 0;
};

class Object3D {
public:
	// Attributes
	bool enabled = true;
	bool selected = false;
	bool anchored = true;

	v3f pos, vel = v3f{};
	c4f c1;
	OBJ_MODIFIERS modifiers;
	
	// Constructors
	Object3D();
	Object3D(const v3f& pos, const c4f& c1);
	Object3D(const DisplayFile& df);
	Object3D(float x, float y, float z);

	// Methods
	virtual const char* name() const { return "OBJETO"; }
	virtual void draw() const;
	virtual void update(const OBJ_MODIFIERS& mdf);
	void rotateY(v3f* v) const;

	template <size_t Length>
	void rotateY(v3f* (&vs)[Length]) const;
	void rotateY(std::vector<v3f>& vs) const;
};

template<size_t Length>
void Object3D::rotateY(v3f* (&vs)[Length]) const {
	for (size_t i = 0; i < Length; ++i)
		rotateY(vs[i]);
}

#endif
