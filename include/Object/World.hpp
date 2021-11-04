#pragma once
#include "Object/Object3D.hpp"
#include <vector>

class World {
private:
	// Attributes
	std::vector<Object3D*> objects;
public:
	// Methods
	void add(Object3D& object);
	void draw() const;
	void update(OBJ_MODIFIERS obj_mdf) const;
};