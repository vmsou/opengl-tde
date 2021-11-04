#pragma once
#include <memory>
#include <vector>
#ifndef POOL_OBJ_HPP
#define POOL_OBJ_HPP

template <typename T>
class PooledObject {
public:
	using ptr = std::unique_ptr<T>;
	static std::vector<ptr> pool;

	template <typename... Args>
	static T& create(Args&&... args);
};

#include "PooledObject.cpp"

#endif
