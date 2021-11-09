#pragma once
#include "Object/Object3D.hpp"
#include <vector>

struct SCENE_MODIFIERS {
	bool light_enabled = true;
	bool rotate_camera = true;
	bool shade_flat = true;
	bool cull_enabled = true;
};

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