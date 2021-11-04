#pragma once

#include <string>

#include "helper.h"
#include "netvars.h"

class ClientClass;
class Matrix;
struct model_t;
class Vector;

enum class ObsMode {
	None = 0,
	Deathcam,
	Freezecam,
	Fixed,
	InEye,
	Chase,
	Roaming
};

class WeaponEntity
{
public:
	void* networkable()
	{
		return reinterpret_cast<void*>(this + 0x8);
	}

	int weaponType()
	{
		return call_virtual_method<int(__thiscall*)(void*)>(this, WEAPONENTITY_WEAPON_TYPE)(this);
	}

	int itemDefinitionIndex()
	{
		return *reinterpret_cast<int*>(this + netvars::itemDefIndex);
	}

	ClientClass* clientClass()
	{
		return call_virtual_method<ClientClass* (__thiscall*)(void*)>(networkable(), ENTITY_CLIENTCLASS)(networkable());
	}

	bool isKnife() { return weaponType() == 0; }
	bool isPistol() { return weaponType() == 1; }
	bool isRevolver() { return (itemDefinitionIndex() == 64 || itemDefinitionIndex() == 262208); }

	std::wstring weaponTypeStr();
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

	int armor()
	{
		return *reinterpret_cast<int*>(this + netvars::armor);
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

	float simulationTime()
	{
		return *reinterpret_cast<float*>(this + netvars::simulationTime);
	}

	int tickBase()
	{
		return *reinterpret_cast<int*>(this + netvars::tickBase);
	}

	bool isAlive()
	{
		return (health() > 0);
	}

	Vector& absOrigin()
	{
		return call_virtual_method<Vector& (__thiscall*)(void*)>(this, ENTITY_ABSORIGIN)(this);
	}

	Vector vecOrigin()
	{
		return *reinterpret_cast<Vector*>(this + netvars::vecOrigin);
	}

	Vector eyePosition()
	{
		Vector v;
		call_virtual_method<void(__thiscall*)(void*, Vector&)>(this, ENTITY_EYEPOS)(this, v);
		return v;
	}

	Vector aimPunch()
	{
		/*Vector v;
		call_virtual_method<void(__thiscall*)(void*, Vector&)>(this, ENTITY_AIMPUNCH)(this, v);
		return v;*/
		return *reinterpret_cast<Vector*>(this + netvars::aimPunch);
	}

	bool isPlayer()
	{
		return call_virtual_method<bool(__thiscall*)(void*)>(this, ENTITY_ISPLAYER)(this);
	}

	ClientClass* clientClass()
	{
		return call_virtual_method<ClientClass* (__thiscall*)(void*)>(networkable(), ENTITY_CLIENTCLASS)(networkable());
	}

	int index()
	{
		return call_virtual_method<int(__thiscall*)(void*)>(networkable(), 10)(networkable());
	}

	bool setupBones(Matrix* out, int max, int mask, float time)
	{
		return call_virtual_method<bool(__thiscall*)(void*, Matrix*, int, int, float)>(animating(), ENTITY_SETUPBONES)(animating(), out, max, mask, time);
	}

	ObsMode observerMode()
	{
		return call_virtual_method<ObsMode(__thiscall*)(void*)>(this, ENTITY_OBSMODE)(this);
	}

	Entity* observerTarget()
	{
		return call_virtual_method<Entity* (__thiscall*)(void*)>(this, ENTITY_OBSTARGET)(this);
	}

	void invalidateBoneCache();

	WeaponEntity* activeWeapon();

	Vector hitboxPos(int id);

	bool isGrenade();

	bool isC4();
	bool isPlantedC4();
};