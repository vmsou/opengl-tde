#include <Windows.h>
#include <functional>

#include "Utils.hpp"
#include "RenderWindow.hpp"
#include "v3f.hpp"
#include "Object/World.hpp"
#include "DisplayReader.hpp"
#include "Geometry/Shapes.hpp"

#ifndef RENDER_WINDOW_CPP
#define RENDER_WINDOW_CPP

struct Camera {
	v3f eye;
	v3f center;
	v3f up;
};

struct Menu {
	int MAIN_MENU, SELECT_MENU, OBJECT_MENU, VALUE, WINDOW;
};

Camera cam{
	v3f{ 0.0f, 0.0f, 300.0f },
	v3f{ 0.0f, 0.0f, 0.0f },
	v3f{ 0.0f, 1.0f, 0.0f }
};

void gluLookAt(const v3f& eye, const v3f& center, const v3f& up) {
	gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z);
}

// Initialize global variables
GLsizei width = 500, height = 500;
GLfloat aspect = width / (GLfloat)height;
GLfloat angleV = 45.0f, angleX = 0.0f, angleY = 0.0f, angleZ = 0.0f;

GLfloat nRange = 200;
World world;

OBJ_MODIFIERS obj_mdf{ true, 0};							// grid, angleY
SCENE_MODIFIERS scn_mdf{ true, true, true, true, false };	// light, camera_rotate, shade_flat, cull_face, ortho_projection

// c4f lightPos{ 0.0f, 150.0f, 500.0f, 1.0f };

Menu menus;

Object3D* context;

void menu(int num) {
	if (num == 0) exit(0);
	else menus.VALUE = num;
}

void object_menu(int num) {
	if (num == 0) {
		context->enabled = context->enabled ? false : true;
		glutSetMenu(menus.OBJECT_MENU);
		glutChangeToMenuEntry(1, context->enabled ? "Desativar" : "Ativar", 0);
	}
	if (num == 1) {
		context->anchored = context->anchored ? false : true;
		glutSetMenu(menus.OBJECT_MENU);
		glutChangeToMenuEntry(2, context->anchored ? "Destravar" : "Travar", 1);
	}
}

void objects_menu(int num) {
	// Create Object Menu
	if (!context) {
		context = world.objects[num];
		context->selected = true;
		std::cout << "Selecionado: " << context->name() << '\n';
		menus.OBJECT_MENU = glutCreateMenu(object_menu);
		glutAddMenuEntry(context->enabled ? "Desativar" : "Ativar", 0);
		glutAddMenuEntry(context->anchored ? "Destravar" : "Travar", 1);
		glutSetMenu(menus.MAIN_MENU);
		glutAddSubMenu(context->name(), menus.OBJECT_MENU);
	} else {
		context->selected = false;
		context = world.objects[num];
		context->selected = true;
		std::cout << "Selecionado: " << context->name() << '\n';
		glutSetMenu(menus.MAIN_MENU);
		glutChangeToSubMenu(3, context->name(), menus.OBJECT_MENU);
	}
}
	
void createGLUTMenus() {
	// SELECT MENU
	menus.SELECT_MENU = glutCreateMenu(objects_menu);
	int id = 0;
	for (const Object3D* obj : world.objects) {
		glutAddMenuEntry(obj->name(), id);
		++id;
	}


	// MAIN MENU
	menus.MAIN_MENU = glutCreateMenu(menu);
	glutAddSubMenu("Select", menus.SELECT_MENU);
	glutAddMenuEntry("Quit", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void RenderWindow::init() {
	auto& cubo = Cube::create(75.0f, v3f{}, getColor("blue"));
	cubo.vel = v3f{ 1, 0.2f, 0.3f };
	cubo.anchored = false;

	auto& bule = make_callback_obj(&glutSolidTeapot, v3f{ -100, 100, 0 }, getColor("red"), 30.0f);
	auto& toroide = make_callback_obj(&glutSolidTorus, v3f{ -100, -100, 0 }, getColor("red"), 10, 30, 20, 20);
	auto& xicara = make_callback_obj(&glutSolidTeacup, v3f{ 100.0f, 100.0f, 0.0f }, getColor("blue"), 30.0f);
	auto& colher = make_callback_obj(&glutSolidTeaspoon, v3f{ 100.0f, -100.0f, 0.0f }, getColor("blue"), 100.0f);
	toroide.frontFace = GL_CCW;

	DisplayArray dArr(source_file);
	std::cout << "Scene:\n";
	std::cout << dArr << "\n\n";
	
	world = World(dArr);
	world.low = -nRange;
	world.high = nRange;

	world.add(cubo);
	world.add(bule);
	world.add(toroide);
	world.add(xicara);
	world.add(colher);
}


void axis() {
	glLineWidth(2.0f);
	glBegin(GL_LINES);
		color("red");
		glVertex3f(0, 0.0f, 0.0f);
		glVertex3f(nRange, 0.0f, 0.0f);
		color("green");
		glVertex3f(0.0f, 0, 0.0f);
		glVertex3f(0.0f, nRange, 0.0f);
		color("blue");
		glVertex3f(0.0f, 0.0f, 0);
		glVertex3f(0.0f, 0.0f, nRange);
	glEnd();
}

void grid() {
	glLineWidth(1.0f);
	glBegin(GL_LINES);
	color("gray");
	for (float i = -nRange; i <= nRange; i += 10) {
		glVertex3f(-nRange, i, 0.0f);
		glVertex3f(nRange, i, 0.0f);

		glVertex3f(i, -nRange, 0.0f);
		glVertex3f(i, nRange, 0.0f);
	}
	glEnd();

	glLineWidth(1.0f);
	color("gray");
	glutWireCube(nRange * 2.0);
}


RenderWindow::RenderWindow(const char* title, int argc, char* argv[], const char* source_file) {
	this->source_file = source_file;

	glutInit(&argc, argv);

	// Make the Window
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);
	glutCreateWindow(title);

	// Initialize glew
	initGlew();

	// Initialize GL
	glViewport(0, 0, width, height);
	glClearColor(getColor("black"));
	glClearDepth(1.0f);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_FLAT);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	c4f ambientLight{ 0.2f, 0.2f, 0.2f, 1.0f };
	c4f diffuseLight{ 0.5f, 0.5f, 0.5, 1.0f };
	c4f specularLight{ 0.5f, 0.5f, 0.5, 1.0f };
	c4f specularity{ 1.0f, 1.0f, 1.0f, 1.0f };
	GLint specMaterial = GLint(40);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specularity);
	glMateriali(GL_FRONT, GL_SHININESS, specMaterial);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularity);
	// glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	// Callbacks
	glutDisplayFunc(&render);				// display
	glutReshapeFunc(&on_size);				// window reshape
	glutIdleFunc(&render);					// idle
	glutTimerFunc(25, &update, 0);			// timer
	glutSpecialFunc(&on_special);			// keyboard
	glutMouseFunc(&on_mouse_button);		// mouse
	glutMouseWheelFunc(&on_mouse_wheel);	// scroll

	init();
	createGLUTMenus();
}

void RenderWindow::run() { glutMainLoop(); }

void RenderWindow::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	setVisParam();

	glRotatef(angleX, 1.0f, 0.0f, 0.0f);
	glRotatef(angleY, 0.0f, 1.0f, 0.0f);
	glRotatef(angleZ, 0.0f, 0.0f, 1.0f);

	world.draw();
	
	if (obj_mdf.grid_enabled) grid();
	axis();

	glutSwapBuffers();
}

void RenderWindow::setVisParam() {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		if (scn_mdf.ortho_projection) {						// Orthogonal
			if (width <= height)
				glOrtho(-nRange, nRange, -nRange * height / width, nRange * height / width, -nRange * 2, nRange * 2);
			else
				glOrtho(-nRange * width / height, nRange * width / height, -nRange, nRange, -nRange * 2, nRange * 2);
		} else 
			gluPerspective(angleV, aspect, 0.1f, 1000.0f);	// Perspective

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(cam.eye, v3f{ 0, 0, 1 }, cam.up);
}

void RenderWindow::on_mouse_button(GLint button, GLint state, GLint x, GLint y) {
	if (state == GLUT_DOWN)
		switch (button) {
		case GLUT_LEFT_BUTTON:
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		}
	else if (state == GLUT_UP)
		switch (button) {
		case GLUT_LEFT_BUTTON:
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		}
	glutPostRedisplay();
}

void RenderWindow::on_mouse_wheel(GLint button, GLint dir, GLint x, GLint y) {
	if (dir > 0) cam.eye.z -= 10;
	else cam.eye.z += 10;
}

void RenderWindow::update(int value) {
	// Pressed
	if (GetAsyncKeyState((unsigned short)'L') & 0x001) {	// Light
		scn_mdf.light_enabled = scn_mdf.light_enabled ? false : true;
		if (scn_mdf.light_enabled) {
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
		} else {
			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);
		}
	}

	if (GetAsyncKeyState((unsigned short)'G') & 0x001) {	// Enable/Disable Grid
		obj_mdf.grid_enabled = obj_mdf.grid_enabled ? false : true;
	}

	if (GetAsyncKeyState((unsigned short)'R') & 0x001) {	// Reset Camera
		angleX = 0.0f; angleY = 0.0f; angleZ = 0.0f;
	}

	if (GetAsyncKeyState((unsigned short)'C') & 0x001) {	// Enable/Disable Cull face
		scn_mdf.cull_enabled = scn_mdf.cull_enabled ? false : true;
		if (scn_mdf.cull_enabled) glEnable(GL_CULL_FACE);
		else glDisable(GL_CULL_FACE);
	}

	if (GetAsyncKeyState((unsigned short)'P') & 0x001) {	// Projection Orthogonal/Perspective
		scn_mdf.ortho_projection = scn_mdf.ortho_projection ? false : true;
		std::cout << "Projecao: ";
		if (scn_mdf.ortho_projection) std::cout << "Ortogonal\n";
		else std::cout << "Perspectiva\n";
		setVisParam();
	}

	// Hold
	if (context) {
		if (GetAsyncKeyState((unsigned short)'W') & 0x8000) context->pos.y += 2.0f;
		if (GetAsyncKeyState((unsigned short)'A') & 0x8000) context->pos.x -= 2.0f;
		if (GetAsyncKeyState((unsigned short)'S') & 0x8000) context->pos.y -= 2.0f;
		if (GetAsyncKeyState((unsigned short)'D') & 0x8000) context->pos.x += 2.0f;
	}
	

	world.update(obj_mdf);

	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}


void RenderWindow::on_special(GLint key, GLint x, GLint y) {
	switch (key) {
	case GLUT_KEY_F1:
		scn_mdf.shade_flat = scn_mdf.shade_flat ? false : true;
		if (scn_mdf.shade_flat) glShadeModel(GL_FLAT);
		else glShadeModel(GL_SMOOTH);
		break;
	case GLUT_KEY_F2:
		scn_mdf.rotate_camera = scn_mdf.rotate_camera ? false : true;
		break;
	case GLUT_KEY_LEFT:
		if (scn_mdf.rotate_camera) angleY += 2.0f;
		else --obj_mdf.angleY;
		break;
	case GLUT_KEY_RIGHT:
		if (scn_mdf.rotate_camera) angleY -= 2.0f;
		else ++obj_mdf.angleY;
		break;
	case GLUT_KEY_UP:
		if (scn_mdf.rotate_camera) angleX += 2.0f;
		break;
	case GLUT_KEY_DOWN:
		if (scn_mdf.rotate_camera) angleX -= 2.0f;
		break;
	case GLUT_KEY_PAGE_DOWN:
		if (scn_mdf.rotate_camera) angleZ -= 2.0f;
		break;
	case GLUT_KEY_PAGE_UP:
		if (scn_mdf.rotate_camera) angleZ += 2.0f;
		break;
	}
}

void RenderWindow::on_size(GLint w, GLint h) {
	width = w;
	height = h == 0 ? 1 : h;
	aspect = width / (GLfloat)height;

	glViewport(0, 0, width, height);
	setVisParam();

	if (scn_mdf.ortho_projection) {
		if (width <= height)
			glOrtho(-nRange, nRange, -nRange * height / width, nRange * height / width, -nRange * 2, nRange * 2);
		else
			glOrtho(-nRange * width / height, nRange * width / height, -nRange, nRange, -nRange * 2, nRange * 2);
	}
}

#endif
