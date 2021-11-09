#pragma once
#include "v3f.hpp"
#include "c4f.hpp"
#include "Object/PooledObject3D.hpp"
#include <tuple>
#include <functional>
#ifndef CALLBACK_OBJ_HPP
#define CALLBACK_OBJ_HPP

template <typename Function, typename... Args>
class CallbackObject : public PooledObject3D<CallbackObject<Function, Args...>> {
private:
	// Attributes
	Function* function;
	std::tuple<Args...> args;

public:
	GLenum frontFace = GL_CW;
	// Constructors
	CallbackObject(Function* function, const v3f& pos, const c4f& c1, const Args&... args);
	
	// Methods
	void draw() const override {
		glFrontFace(frontFace);
		glPushMatrix();
		glColor3f(this->c1);
		glTranslatef(this->pos);
		glRotatef((GLfloat)this->modifiers.angleY, 0.0f, 1.0f, 0.0f);
		std::apply(function, args);
		glPopMatrix();
		glFrontFace(GL_CCW);
	}

};

// Functions
template <typename Function, typename... Args>
CallbackObject<Function, Args...>& make_callback_obj(Function* function, const v3f& pos, const c4f& c1, const Args&... args);

#include "CallbackObject.cpp"

#endif