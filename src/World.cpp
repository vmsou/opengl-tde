#include "Object/World.hpp"

// Constructors
World::World(const DisplayArray& dArr) {
	for (const DisplayFile& df : dArr) {
		if (df.type == 1) this->add(Disc::create(df));
		else if (df.type == 2) this->add(Cone::create(df));

	}
}

// Methods
void World::add(Object3D& object) { objects.push_back(&object); }

void World::draw() const {
	for (const Object3D* obj : objects)
		obj->draw();
}

void World::update(OBJ_MODIFIERS obj_mdf) const {
	for (Object3D* obj : objects)
		obj->update(obj_mdf);
}
