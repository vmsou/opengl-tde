#include "Object/World.hpp"

template <typename T>
Object3D& make(const DisplayFile& df) { return T::create(df); }

// Constructors
World::World(const DisplayArray& dArr) {
	for (const DisplayFile& df : dArr) {
		switch (df.type) {
			case 1:
				this->add(make<Disc>(df));
				break;
			case 2:
				this->add(make<Cone>(df));
				break;
			case 3:
				this->add(make<Tetrahedron>(df));
				break;
		}
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
