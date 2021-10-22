#pragma once

#include "helper.h"
#include "netvars.h"

class ClientClass;
class Matrix;
struct model_t;
class Vector;

class WeaponEntity
{
public:
	int weaponType()
	{
		return call_virtual_method<int(__thiscall*)(void*)>(this, WEAPONENTITY_WEAPON_TYPE)(this);
	}

	int itemDefinitionIndex()
	{
		return *reinterpret_cast<int*>(this + netvars::itemDefIndex);
	}

	bool isKnife() { return weaponType() == 0; }
	bool isPistol() { return weaponType() == 1; }
	bool isRevolver() { return (itemDefinitionIndex() == 64 || itemDefinitionIndex() == 262208); }
};

class Entity
{
public:
	void* animating()
	{
		return reinterpret_cast<void*>(this + 0x4);
	}

	void* networkable()
	{
		return reinterpret_cast<void*>(this + 0x8);
	}

	model_t* model()
	{
		return call_virtual_method<model_t* (__thiscall*)(void*)>(animating(), ENTITY_MODEL)(animating());
	}

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

	bool isAlive()
	{
		return (health() > 0);
	}

	Vector& absOrigin()
	{
		return call_virtual_method<Vector& (__thiscall*)(void*)>(this, ENTITY_ABSORIGIN)(this);
	}

	Vector eyePosition()
	{
		Vector v;
		call_virtual_method<void(__thiscall*)(void*, Vector&)>(this, ENTITY_EYEPOS)(this, v);
		return v;
	}

	Vector aimPunch()
	{
		Vector v;
		call_virtual_method<void(__thiscall*)(void*, Vector&)>(this, ENTITY_AIMPUNCH)(this, v);
		return v;
	}

	bool isPlayer()
	{
		return call_virtual_method<bool(__thiscall*)(void*)>(this, ENTITY_ISPLAYER)(this);
	}

	ClientClass* clientClass()
	{
		return call_virtual_method<ClientClass* (__thiscall*)(void*)>(networkable(), ENTITY_CLIENTCLASS)(networkable());
	}

	bool setupBones(Matrix* out, int max, int mask, float time)
	{
		return call_virtual_method<bool(__thiscall*)(void*, Matrix*, int, int, float)>(animating(), ENTITY_SETUPBONES)(animating(), out, max, mask, time);
	}

	WeaponEntity* activeWeapon();

	Vector hitboxPos(int id);

	bool isGrenade();
};