#pragma once
#include "Object/Object3D.hpp"
#ifndef OBJ_3D_CPP
#define OBJ_3D_CPP

// Constructors
Object3D::Object3D() : pos{}, c1{}, modifiers{ true, 0 } {}
Object3D::Object3D(const v3f& pos, const c4f& c1) : pos{ pos }, c1{ c1 }, modifiers{ true, 0 } {}
Object3D::Object3D(const DisplayFile& df) : Object3D{ df.pos, df.color } {}
Object3D::Object3D(float x, float y, float z) : pos{ x, y, z }, modifiers{ true, 0 } {}

// Methods
void Object3D::draw() const {}
void Object3D::update(const OBJ_MODIFIERS& mdf) { this->modifiers = mdf; }

void Object3D::rotateY(v3f* v) const {
	const float rad = (float)(modifiers.angleY * M_PI) / 180.0f;
	const float sinTheta = sin(rad);
	const float cosTheta = cos(rad);

	const float x = v->x;
	const float z = v->z;

	v->x = (x * cosTheta) + (z * sinTheta);
	v->z = (z * cosTheta) - (x * sinTheta);
}

void Object3D::rotateY(std::vector<v3f>& vs) const {
	for (v3f& v : vs)
		rotateY(&v);
}

#endif
