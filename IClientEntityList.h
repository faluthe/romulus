#pragma once

#include "Entity.h"
#include "helper.h"

class IClientEntityList
{
public:
	Entity* GetClientEntity(int entNum)
	{
		return call_virtual_method<Entity* (__thiscall*)(void*, int)>(this, ENTLIST_GETENT)(this, entNum);
	}
};