#pragma once
#include "Geometry/CallbackObject.hpp"
#ifndef CALLBACK_OBJ_CPP
#define CALLBACK_OBJ_CPP

template <typename Function, typename... Args>
CallbackObject<Function, Args...>::CallbackObject(Function* function, const v3f& pos, const c4f& c1, const Args&... args)
	: PooledObject3D <CallbackObject<Function, Args...>>{ pos }, function{ function }, c1{ c1 }, args{ args... }{}

template <typename Function, typename... Args>
CallbackObject<Function, Args...>& make_callback_obj(Function* function, const v3f& pos, const c4f& c1, const Args&... args) {
	return CallbackObject<Function, Args...>::create(function, pos, c1, args...);
}


#endif
