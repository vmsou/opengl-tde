#pragma once
#include "Geometry/Cone.hpp"
#ifndef CONE_OBJ_HPP
#define CONE_OBJ_HPP

Cone::Cone(double height, int sides, double radius, v3f pos, c4f c1)
	: PooledObject3D<Cone>(pos), height{ height }, sides{ sides }, radius{ radius }, c1{ c1 }, c2{ c1 }, base{ sides, radius, pos, c1, c2, -1 } {}

Cone::Cone(double height, int sides, double radius, v3f pos, c4f c1, c4f c2) : Cone{ height, sides, radius, pos, c1 } { this->c2 = c2; }

void Cone::draw() const {
	base.draw();

	glPolygonMode(GL_FRONT, GL_FILL);

	double angle = 0.0;
	double max_angle = 2.0 * M_PI;
	const double step = max_angle / sides;

	std::vector<v3f>vs;
	std::vector<std::pair<v3f, v3f>> normals;
	vs.reserve(sides);
	normals.reserve(sides);

	const v3f& p1{ pos.x, pos.y, pos.z + (float)height };

	while (angle <= max_angle) {
		vs.emplace_back(
			pos.x + (float)radius * (float)cos(angle),
			pos.y + (float)radius * (float)sin(angle),
			pos.z
		);
		angle += step;
	}

	const size_t length = vs.size() - 1;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(c1);
	glVertex3f(p1);

	for (size_t i{}; i < length; ++i) {
		const v3f& p2 = vs[i];
		const v3f& p3 = vs[i + 1];

		const v3f v1 = p1 - p2;
		const v3f v2 = p2 - p3;
		const v3f normal = cross(v1, v2).normalize();

		glNormal3f(normal);
		glVertex3f(p1);
		glVertex3f(p2);
		glVertex3f(p3);

		const v3f c = (p1 + p2 + p3) / 3.0f;
		normals.emplace_back(std::make_pair(c, normal));
	}

	glEnd();

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
#endif