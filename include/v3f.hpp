#pragma once
#include <iostream>
#include "c4f.hpp"
#ifndef V3F_HPP
#define V3F_HPP

struct v3f {
	float x, y, z;
	c4f c1;

	// Constructors
	v3f();
	v3f(float x, float y, float z);
	v3f(float x, float y, float z, c4f c1);
	v3f(const v3f& other);
	v3f(const v3f& other, c4f c1);
	v3f(v3f&& other) noexcept;

	// Methods
	void draw(float xpos, float ypos, float zpos) const {
		glColor3f(c1.r, c1.g, c1.b);
		glLineWidth(3.0f);
		glBegin(GL_LINES);
		glVertex3f(xpos, ypos, zpos);
		glVertex3f(xpos + x, ypos + y, zpos + z);
		glEnd();
		glPushMatrix();
		glTranslatef(xpos + x, ypos + y, zpos + z);
		glutSolidSphere(5, 5, 5);
		glPopMatrix();
		glLineWidth(1.0f);
	}

	void move3D(const v3f& other);
	v3f& normalize();
	float length() const;
	v3f normalized() const;

	// Operators
	// Vectorial
	v3f& operator=(const v3f& other);
	v3f& operator=(v3f&& other) noexcept;
	v3f& operator+=(const v3f& other);
	v3f& operator*=(const v3f& other);
	v3f& operator*=(const v3f&& other);

	// Scalar
	v3f& operator*=(float d);
	v3f& operator/=(float d);
};

// Operators Overload
v3f operator+(const v3f& v1, const v3f& v2);	// Soma vetores
v3f operator-(const v3f& v1, const v3f& v2);	// Subtrai vetores
v3f operator*(const v3f& v, float d);			// Multiplicação escalar
v3f operator/(const v3f& v, float d);			// Divisão escalar

// Functions
float dot(const v3f& v1, const v3f& v2);		// Produto escalar
v3f cross(const v3f& v1, const v3f& v2);		// Produto vetorial
float distance(const v3f& v1, const v3f& v2);	// Magnitude

// Overloads
void glVertex3f(const v3f& v);
void glNormal3f(const v3f& v);
void glTranslatef(const v3f& v);
void glLightfv(GLenum face, GLenum pname, const v3f& v);

std::ostream& operator<<(std::ostream& os, const v3f& v);
std::istream& operator>>(std::istream& os, v3f& v);

#endif