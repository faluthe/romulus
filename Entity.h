#pragma once

#include "helper.h"
#include "netvars.h"

class Entity
{
public:
	int health()
	{
		return *reinterpret_cast<int*>(this + netvars::health);
	}

	int flags()
	{
		return *reinterpret_cast<int*>(this + netvars::flags);
	}

	int moveType()
	{
		return *reinterpret_cast<int*>(this + netvars::moveType);
	}

	unsigned char dormant()
	{
		return *reinterpret_cast<unsigned char*>(this + 0xED);
	}

	int team()
	{
		return *reinterpret_cast<int*>(this + netvars::team);
	}

	bool isScoped()
	{
		return *reinterpret_cast<bool*>(this + netvars::isScoped);
	}

	float nextPrimaryAttack()
	{
		return *reinterpret_cast<float*>(this + netvars::nextPrimaryAttack);
	}

	int itemDefinitionIndex()
	{
		return *reinterpret_cast<int*>(this + netvars::itemDefIndex);
	}

	Entity* activeWeapon()
	{
		return call_virtual_method<Entity* (__thiscall*)(void*)>(this, ENTITY_ACTIVE_WEAPON)(this);
	}

	int weaponType()
	{
		return call_virtual_method<int(__thiscall*)(void*)>(this, ENTITY_WEAPON_TYPE)(this);
	}
};