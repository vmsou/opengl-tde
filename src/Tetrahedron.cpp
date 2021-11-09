#pragma once
#include "Geometry/Tetrahedron.hpp"
#ifndef TETRAHEDRON_OBJ_CPP
#define TETRAHEDRON_OBJ_CPP

Tetrahedron::Tetrahedron(const DisplayFile& df) : PooledObject3D<Tetrahedron>(pos, c1) {
	const JSONObject& obj = df.data;
	if (obj.has("size")) this->size = obj.get<float>("size");	else this->size = 50.0f;

}

Tetrahedron::Tetrahedron(float size, const v3f& pos, const c4f& c1) : PooledObject3D<Tetrahedron>(pos, c1), size{ size } {}

void Tetrahedron::draw() const {
	glPolygonMode(GL_FRONT, GL_FILL);

	const float angle = (float)(30.0f * M_PI) / 180.0f;

	v3f p1{ pos.x, pos.y, size + pos.z };
	v3f p2{ size * cos(angle) + pos.x, -size * sin(angle) + pos.y, pos.z };
	v3f p3{ -size * cos(angle) + pos.x, -size * sin(angle) + pos.y, pos.z };
	v3f p4{ pos.x, size + pos.y, pos.z };

	v3f* ps[]{ &p1, &p2, &p3, &p4 };
	rotateY(ps);

	const v3f* f1[]{ &p1, &p2, &p3 };
	const v3f* f2[]{ &p1, &p4, &p2 };
	const v3f* f3[]{ &p1, &p3, &p4 };
	const v3f* f4[]{ &p4, &p3, &p2 };

	glColor3f(c1);
	addVertices(f1);
	addVertices(f2);
	addVertices(f3);
	addVertices(f4);
}

template <size_t Length>
void Tetrahedron::addVertices(const v3f* (&face)[Length]) const {
	const v3f v1 = *face[0] - *face[1];
	const v3f v2 = *face[2] - *face[1];
	v3f out = cross(v1, v2).normalize();
	v3f c{};

	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLES);
	glColor3f(c1);
	glNormal3f(out);
	for (size_t i = 0; i < Length; ++i) {
		glVertex3f(*face[i]);
		c += *face[i];
	}
	glEnd();
	glFrontFace(GL_CCW);

	if (modifiers.grid_enabled) {
		c /= Length;
		glBegin(GL_LINES);
		glColor3f(getColor("white"));
		glVertex3f(c);
		glVertex3f(c + (out * size));
		glEnd();
	}
}

#endif
