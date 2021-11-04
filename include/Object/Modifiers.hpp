#pragma once

struct OBJ_MODIFIERS {
	bool grid_enabled = true;
	int angleY = 0;
};

struct SCENE_MODIFIERS {
	bool light_enabled = true;
	bool rotate_camera = true;
	bool shade_flat = true;
	bool cull_enabled = true;
};