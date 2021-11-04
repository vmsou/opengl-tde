#pragma once
#include <GL\glew.h>
#include <GL\freeglut.h>  // GLUT, include glu.h and gl.h
#include <unordered_map>
#ifndef C4F_HPP
#define C4F_HPP

struct c4f {
	// Attributes
	float r, g, b, a;

	// Constructors
	c4f();
	c4f(float r, float g, float b, float a);
};

// Functions
c4f getColor(const char* name);
void color(const char* name);

// Overloads
void glColor3f(const c4f& c);
void glClearColor(const c4f& c);
void glMaterialfv(GLenum face, GLenum pname, const c4f& c);
void glLightModelfv(GLenum pname, const c4f& c);
void glLightfv(GLenum face, GLenum pname, const c4f& c);

#endif