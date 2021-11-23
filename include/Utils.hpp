#pragma once
#include <GL\glew.h>
#include <GL\freeglut.h>  // GLUT, include glu.h and gl.h
#include <iostream>
#include <stdio.h>


inline GLenum initGlew() {
	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	if (err != GLEW_OK) {
		std::cerr << "Error: " << glewGetErrorString(err) << '\n';
	}

	std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << '\n';
	return err;
}

inline void print_version() {
	// get version info
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << '\n';
	std::cout << "OpenGL version supported: " << glGetString(GL_VERSION) << "\n\n";
}