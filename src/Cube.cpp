#pragma once
#include "Geometry/Cube.hpp"
#ifndef CUBE_OBJ_CPP
#define CUBE_OBJ_CPP

Cube::Cube(float a, v3f pos, c4f c1) : PooledObject3D<Cube>{ pos }, a{ a }, c1{ c1 } {}

void Cube::draw() const {
	glPolygonMode(GL_FRONT, GL_FILL);

	const GLfloat s = a / 2.0f;

	v3f p1 = v3f{ -s, s, s } + pos;		// A
	v3f p2 = v3f{ -s , -s, s } + pos;	// B
	v3f p3 = v3f{ s, s, s } + pos;		// C
	v3f p4 = v3f{ s, -s, s } + pos;		// D
	v3f p5 = v3f{ s, s, -s } + pos;		// E
	v3f p6 = v3f{ s, -s, -s } + pos;	// F
	v3f p7 = v3f{ -s, s, -s } + pos;	// G
	v3f p8 = v3f{ -s, -s, -s } + pos;	// H

	v3f* vs[]{ &p1, &p2, &p3, &p4, &p5, &p6, &p7, &p8 };
	rotateY(vs);

	const v3f* f1[]{ &p1, &p2, &p3, &p4 };		// frente
	const v3f* f2[]{ &p3, &p4, &p5, &p6 };		// direita
	const v3f* f3[]{ &p5, &p6, &p7, &p8 };		// trás
	const v3f* f4[]{ &p7, &p8, &p1, &p2 };		// esquerda
	const v3f* f5[]{ &p1, &p3, &p7, &p5 };		// topo
	const v3f* f6[]{ &p4, &p2, &p6, &p8 };		// baixo

	addVertices(f1);
	addVertices(f2);
	addVertices(f3);
	addVertices(f4);
	addVertices(f5);
	addVertices(f6);
}

template <size_t Length>
v3f Cube::middlePoint(const v3f(&vs)[Length]) const {
	v3f c{};
	for (size_t i{}; i < Length; ++i)
		c += vs[i];
	c /= Length;
	return c;
}

template <size_t Length>
void Cube::addVertices(const v3f* (&face)[Length]) const {
	const v3f v1 = *face[0] - *face[1];
	const v3f v2 = *face[1] - *face[2];
	const v3f out = cross(v1, v2).normalize();
	const v3f m1 = (*face[0] + *face[1] + *face[2]) / 3.0f;
	const v3f m2 = (*face[1] + *face[2] + *face[3]) / 3.0f;

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(c1);
	glNormal3f(out);
	for (size_t i = 0; i < Length; ++i) {
		glNormal3f(out);
		glVertex3f(*face[i]);
	}
	glEnd();


	if (modifiers.grid_enabled) {
		glBegin(GL_LINES);
		glColor3f(getColor("white"));
		glVertex3f(m1);
		glVertex3f(m1 + (out * (a / 2.0f)));
		glVertex3f(m2);
		glVertex3f(m2 + (out * (a / 2.0f)));
		glEnd();
	}

}

#endif