#pragma once
#include "Geometry/Disc.hpp"
#ifndef DISC_OBJ_CPP
#define DISC_OBJ_CPP

Disc::Disc(const DisplayFile& df) : PooledObject3D<Disc>{ df.pos, df.color } {
	const JSONObject& obj = df.data;
	if (obj.has("sides")) this->sides = obj.get<int>("sides");		else this->sides = 10;
	if (obj.has("radius")) this->radius= obj.get<double>("radius"); else this->radius= 50.0;
	if (obj.has("dir")) this->dir= obj.get<int>("dir");				else this->dir = 1;
}

Disc::Disc(int sides, double radius, const v3f& pos, const c4f& c1, int dir)
	: PooledObject3D<Disc>(pos, c1), sides{ sides }, radius{ radius }, c2{ c1 }, dir{ dir } {}

Disc::Disc(int sides, double radius, const v3f& pos, const c4f& c1, const c4f& c2, int dir)
	: Disc(sides, radius, pos, c1, dir) { this->c2 = c2; }

void Disc::draw() const {
	glPolygonMode(GL_FRONT, GL_FILL);

	double angle = 0.0;
	double max_angle = 2.0 * M_PI;
	const double step = max_angle / sides;

	std::vector<v3f>vs;
	std::vector<std::pair<v3f, v3f>> normals;
	vs.reserve(sides);
	normals.reserve(sides);

	const v3f p1 = pos;
	v3f p1_normal = dir > 0 ? v3f{ 0, 0, 1 } : v3f{ 0, 0, -1 };

	normals.push_back(std::make_pair(p1, p1_normal));

	while (angle <= max_angle) {
		vs.emplace_back(
			pos.x + (float)radius * (float)cos(angle),
			pos.y + (float)radius * (float)sin(angle),
			p1.z
		);
		angle += step;
	}

	const size_t length = vs.size() - 1;
	const float dir_mul = dir > 0 ? -1.0f : 1.0f;

	if (dir < 0) glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(c1);
	glNormal3f(p1_normal);
	glVertex3f(p1);

	for (size_t i{}; i < length; ++i) {
		const v3f& p2 = vs[i];
		const v3f& p3 = vs[i + 1];

		const v3f v1 = p1 - p2;
		const v3f v2 = p3 - p2;
		const v3f normal = cross(v1, v2).normalize() *= dir_mul;

		glNormal3f(normal);
		glVertex3f(p1);
		glVertex3f(p2);
		glVertex3f(p3);

		const v3f c = (p1 + p2 + p3) / 3.0f;
		normals.emplace_back(std::make_pair(c, normal));
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

#endif