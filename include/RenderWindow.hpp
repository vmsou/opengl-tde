#pragma once
#include <GL\glew.h>
#include <GL\freeglut.h>  // GLUT, include glu.h and gl.h
#ifndef RENDER_WINDOW_HPP
#define RENDER_WINDOW_HPP

class RenderWindow {
public:
	const char* source_file;
public:
	RenderWindow(const char* title, int argc, char* argv[], const char* source_file);

	/* Main Loop */
	static void run();

	/* Each frame */
	static void render();

	/* Changes values */
	static void update(int value);

	/* Projection and Modelview */
	static void setVisParam();

	/* Mouse callback */
	static void on_mouse_button(GLint button, GLint state, GLint x, GLint y);

	/* Scrollwhell callback */
	static void on_mouse_wheel(GLint button, GLint dir, GLint x, GLint y);

	/* Keyboard callback */
	static void on_special(GLint key, GLint x, GLint y);

	/* Windows Resize callback */
	static void on_size(GLint w, GLint h);

	/* Geometry defining, VAO and VBOs */
	void init();

};

#endif
