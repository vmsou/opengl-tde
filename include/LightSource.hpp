#pragma once
#include "Object/PooledObject3D.hpp"
#include "c4f.hpp"

class LightSource : public PooledObject3D<LightSource> {
public:
	// Constructors
	LightSource(const DisplayFile& df): PooledObject3D<LightSource>(df.pos, df.color) {}

	// Methods
	const char* name() const override { return "Luz"; }

	void update(const OBJ_MODIFIERS& obj) {
		c4f lightPos{ 0.0f, 150.0f, 500.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
		if (this->enabled) {
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
		} else {
			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);
		}
	}
};