#pragma once
#include "Object3D.hpp"
#include "PooledObject.hpp"
#ifndef POOL_OBJ_3D_HPP
#define POOL_OBJ_3D_HPP

template <typename T>
class PooledObject3D : public Object3D, public PooledObject<T> {
public:
	// Constructors
	PooledObject3D();

	template <typename... Args>
	PooledObject3D(Args&&...args);

	// Methods
	static void clean();
};

#include "PooledObject3D.cpp"

#endif
