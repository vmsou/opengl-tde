#pragma once
#include "Geometry/Cylinder.hpp"

Cylinder::Cylinder(double size, int sides, int sections, double radius, const v3f& pos, const c4f& c1)
	: PooledObject3D<Cylinder>(pos), size{ size }, sides{ sides }, sections{ sections }, radius{ radius }, c1{ c1 },
	  d1{ sides, radius, pos, c1, -1 }, 
	  d2{ sides, radius, v3f{pos.x, pos.y, pos.z + (float)size}, c1, 1 } {}


void Cylinder::draw() const {
	d1.draw();
	d2.draw();

	glPolygonMode(GL_FRONT, GL_FILL);

	double max_angle = 2.0 * M_PI;
	const double step = max_angle / sides;

	std::vector<v3f>vs;
	std::vector<std::pair<v3f, v3f>> normals;
	vs.reserve(sides * (long long)sections);
	normals.reserve(sides * (long long)sections);

	const float size_step = (float)size / (float)sections;

	float z = pos.z;
	for (int section = 0; section < sections; ++section) {
		for (double angle = 0.0f; angle <= max_angle; angle += step) {
			for (int i = 0; i < 2; ++i) {
				vs.emplace_back(
					pos.x + (float)radius * (float)cos(angle),
					pos.y + (float)radius * (float)sin(angle),
					i & 1 ? z + size_step : z
				);
			}
		}
		z += size_step;
	}
	
	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(c1);
	const size_t length = vs.size() - 2;

	for (size_t i = 0; i < length; ++i) {
		const v3f& p1 = vs[i];
		const v3f& p2 = vs[i + 1];
		const v3f& p3 = vs[i + 2];

		const v3f v1 = p1 - p2;
		const v3f v2 = p3.z > p2.z ? p2 - p3 : p3 - p2;
		const v3f normal = cross(v1, v2).normalize();
		glNormal3f(normal);
		glVertex3f(p1);
		glVertex3f(p2);
		glVertex3f(p3);

		const v3f c = (p1 + p2 + p3) / 3.0f;
		normals.emplace_back(c, normal);
	}

	glEnd();
	glFrontFace(GL_CCW);

	if (modifiers.grid_enabled) {
		glBegin(GL_LINES);
		glColor3f(getColor("white"));
		for (const auto& [c, normal] : normals) {
			glVertex3f(c);
			glVertex3f(c + (normal * (float)radius));
		}
		glEnd();
	}
}