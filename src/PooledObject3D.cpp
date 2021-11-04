#pragma once
#include "Object/PooledObject3D.hpp"
#ifndef POOL_OBJ_3D_CPP
#define POOL_OBJ_3D_CPP

// Constructors
template <typename T>
PooledObject3D<T>::PooledObject3D() : Object3D() {}

template <typename T>
template <typename... Args>
PooledObject3D<T>::PooledObject3D(Args&&...args) : Object3D(args...) {}

// Methods
template <typename T>
void PooledObject3D<T>::clean() {
	PooledObject<T>::pool.clear();
}

#endif
