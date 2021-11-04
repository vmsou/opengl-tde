#pragma once
#include "c4f.hpp"
#ifndef C4F_CPP
#define C4F_CPP

// Constructors
c4f::c4f() : r{}, g{}, b{}, a{} {}
c4f::c4f(float r, float g, float b, float a) : r{ r }, g{ g }, b{ b }, a{ a } {}

// Functions
c4f getColor(const char* name) {
	static std::unordered_map<const char*, c4f> colors{
		{ "red", { 1.0f, 0.0f, 0.0f, 1.0f} }, { "green", { 0.0f, 1.0f, 0.0f, 1.0f } }, { "blue", { 0.0f, 0.0f, 1.0f, 1.0f } },
		{ "yellow", { 1.0f, 1.0f, 0.0f, 1.0f} }, { "orange", { 0.8f, 0.3f, 0.02f, 1.0f}, }, { "gray", { 0.3f, 0.3f, 0.3f, 1.0f} },
		{ "black", { 0.0f, 0.0f, 0.0f, 1.0f} }, { "white", {1.0f, 1.0f, 1.0f, 1.0f } }, { "cyan", {0.0f, 1.0f, 1.0f, 1.0f } },
		{ "pink", {1.0f, 0.07f, 0.57f, 1.0f } }, { "navyblue", { 0.07f, 0.13f, 0.17f, 1.0f } }
	};

	return colors[name];
}

void color(const char* name) { glColor3f(getColor(name)); }

// Overloads
void glColor3f(const c4f& c) {
	glColor3f(c.r, c.g, c.b);
}

void glClearColor(const c4f& c) {
	glClearColor(c.r, c.g, c.b, c.a);
}

void glMaterialfv(GLenum face, GLenum pname, const c4f& c) {
	GLfloat a[]{ c.r, c.g, c.b, c.a };
	glMaterialfv(face, pname, a);
}

void glLightModelfv(GLenum pname, const c4f& c) {
	GLfloat a[]{ c.r, c.g, c.b, c.a };
	glLightModelfv(pname, a);
}

void glLightfv(GLenum face, GLenum pname, const c4f& c) {
	GLfloat a[]{ c.r, c.g, c.b, c.a };
	glLightfv(face, pname, a);
}

#endif