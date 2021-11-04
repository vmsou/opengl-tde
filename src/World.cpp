#include "Object/World.hpp"

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