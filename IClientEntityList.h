#pragma once

#include "Entity.h"
#include "helper.h"

class IClientEntityList
{
public:
	template<typename T>
	T* GetClientEntity(int index)
	{
		return call_virtual_method<T*, 3>(this, index);
	}

	template<typename T>
	T* GetEntityFromHandle(int handle)
	{
		return call_virtual_method<T*, 4>(this, handle);
	}

	VIRTUAL_METHOD(int, GetMaxEntities, 8, (), (this))
};