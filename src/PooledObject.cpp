#pragma once
#include "Object/PooledObject.hpp"
#ifndef POOL_OBJ_CPP
#define POOL_OBJ_CPP

// Attributes
template <typename T>
std::vector<std::unique_ptr<T>> PooledObject<T>::pool;

// Methods
template <typename T>
template <typename... Args>
static T& PooledObject<T>::create(Args&&... args) {
	ptr new_obj = std::make_unique<T>(args...);
	pool.push_back(std::move(new_obj));
	return *pool.back();
}

#endif
