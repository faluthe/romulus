#pragma once

#include "Entity.h"
#include "helper.h"

class Entity;

class IClientEntityList
{
public:
	Entity* GetClientEntity(int entNum)
	{
		return call_virtual_method<Entity* (__thiscall*)(void*, int)>(this, ENTLIST_GETENT)(this, entNum);
	}

	int GetMaxEntities()
	{
		return call_virtual_method<int(__thiscall*)(void*)>(this, ENTLIST_MAXENTS)(this);
	}
};