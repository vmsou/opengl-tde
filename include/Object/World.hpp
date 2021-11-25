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
public:
	// Attributes
	float low, high;
	std::vector<Object3D*> objects;
	v3f gravity = v3f{ 0, -0.2f, 0 };
public:
	World() = default;
	World(const DisplayArray& arr);
	
	// Methods
	void add(Object3D& object);
	void draw() const;
	void update(OBJ_MODIFIERS obj_mdf) const;
};
