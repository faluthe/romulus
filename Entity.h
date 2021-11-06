#pragma once

#include <string>

#include "helper.h"
#include "netvars.h"

class ClientClass;
struct CUserCmd;
class Matrix;
struct model_t;
class WeaponEntity;
class Vector;

enum class OBSMode 
{
	None = 0,
	Deathcam,
	Freezecam,
	Fixed,
	InEye,
	Chase,
	Roaming
};

enum class Team
{
	T = 2,
	CT = 3
};

class Entity
{
public:
	void* animating() { return reinterpret_cast<void*>(this + 0x4); }
	void* networkable() { return reinterpret_cast<void*>(this + 0x8); }

	VIRTUAL_METHOD(ClientClass*, clientClass, 2, (), (networkable()))
	VIRTUAL_METHOD(model_t*, model, 8, (), (animating()))
	VIRTUAL_METHOD(Vector&, absOrigin, 10, (), (this))
	VIRTUAL_METHOD(bool, setupBones, 13, (Matrix* out, int maximum, int mask, float time), (animating(), out, maximum, mask, time))

	NETVAR(int, modelIndex, "DT_BaseViewModel", "m_nModelIndex")

	Vector hitboxPos(int id);
	bool isGrenade();
	bool isC4();
	bool isPlantedC4();
};

class PlayerEntity : public Entity
{
public:
	VIRTUAL_METHOD(bool, isPlayer, 158, (), (this))
	VIRTUAL_METHOD(int, entityListIndex, 10, (), (networkable()))
	VIRTUAL_METHOD(OBSMode, observerMode, 294, (), (this))
	VIRTUAL_METHOD(Entity*, observerTarget, 295, (), (this))

	NETVAR(int, health, "DT_BasePlayer", "m_iHealth")
	NETVAR(int, armor, "DT_CSPlayer", "m_ArmorValue")
	NETVAR(int, flags, "DT_CSPlayer", "m_fFlags")
	NETVAR(Team, team, "DT_BasePlayer", "m_iTeamNum")
	NETVAR(bool, isScoped, "DT_CSPlayer", "m_bIsScoped")
	NETVAR(float, simulationTime, "DT_CSPlayer", "m_flSimulationTime")
	NETVAR(int, tickBase, "DT_CSPlayer", "m_nTickBase")
	NETVAR(bool, gunGameImmunity, "DT_CSPlayer", "m_bGunGameImmunity")
	NETVAR(Vector, vecOrigin, "DT_BasePlayer", "m_vecOrigin")

	bool isAlive() { return (health() > 0); }
	void invalidateBoneCache();
	WeaponEntity* activeWeapon();
	
	int moveType() { return *reinterpret_cast<int*>(this + netvars::moveType); } // REDO
	unsigned char dormant() { return *reinterpret_cast<unsigned char*>(this + 0xED); }
	Vector eyePosition()
	{
		Vector v;
		call_virtual_method<void, 285>(this, std::ref(v));
		return v;
	}
};

class LocalplayerEntity : public PlayerEntity
{
public:
	NETVAR(unsigned int*, weapons, "DT_CSPlayer", "m_hMyWeapons")
	NETVAR(Vector, aimPunch, "DT_BasePlayer", "m_aimPunchAngle")
	NETVAR(int, viewmodel, "DT_BasePlayer", "m_hViewModel[0]")
	void aimAt(Vector pos, CUserCmd* cmd, bool silent = true);
};

class WeaponEntity : public Entity
{
public:
	VIRTUAL_METHOD(int, weaponType, 455, (), (this))

	NETVAR(int, itemDefIndex, "DT_BaseCombatWeapon", "m_iItemDefinitionIndex")
	NETVAR(int, paintKit, "DT_BaseAttributableItem", "m_nFallbackPaintKit")
	NETVAR(int, quality, "DT_BaseAttributableItem", "m_iEntityQuality")
	NETVAR(float, wear, "DT_BaseAttributableItem", "m_flFallbackWear")
	NETVAR(int, ogOwnerLow, "DT_BaseAttributableItem", "m_OriginalOwnerXuidLow")
	NETVAR(int, ogOwnerHigh, "DT_BaseAttributableItem", "m_OriginalOwnerXuidHigh")
	NETVAR(int, fallbackSeed, "DT_BaseAttributableItem", "m_nFallbackSeed")
	NETVAR(int, itemId, "DT_BaseAttributableItem", "m_iItemIDHigh")
	NETVAR(int, hWorldModel, "DT_BaseCombatWeapon", "m_hWeaponWorldModel")
	
	bool isKnife() { return weaponType() == 0; }
	bool isPistol() { return weaponType() == 1; }
	bool isRevolver() { return (itemDefIndex() == 64 || itemDefIndex() == 262208); }

	std::wstring weaponTypeStr();
};

class ViewmodelEntity : public Entity
{
public:
	NETVAR(int, hWeapon, "DT_BaseViewModel", "m_hWeapon")
};