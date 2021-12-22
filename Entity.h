#pragma once

#include <string>

#include "config.h"
#include "helper.h"
#include "netvars.h"

class ClientClass;
struct CUserCmd;
class Matrix;
struct model_t;
class WeaponEntity;
struct WeaponInfo;
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

enum class WeaponType
{
	Knife = 0,
	Pistol,
	SubMachinegun,
	Rifle,
	Shotgun,
	SniperRifle,
	Machinegun,
	C4,
	Placeholder,
	Grenade,
};

class Collideable
{
public:
	VIRTUAL_METHOD(const Vector&, obbMins, 1, (), (this))
	VIRTUAL_METHOD(const Vector&, obbMaxs, 2, (), (this))
};

class Entity
{
public:
	void* animating() { return reinterpret_cast<void*>(this + 0x4); }
	void* networkable() { return reinterpret_cast<void*>(this + 0x8); }

	VIRTUAL_METHOD(ClientClass*, clientClass, 2, (), (networkable()))
	VIRTUAL_METHOD(Collideable*, getCollideable, 3, (), (this))
	VIRTUAL_METHOD(model_t*, model, 8, (), (animating()))
	VIRTUAL_METHOD(Vector&, absOrigin, 10, (), (this))
	VIRTUAL_METHOD(bool, setupBones, 13, (Matrix* out, int maximum, int mask, float time), (animating(), out, maximum, mask, time))

	NETVAR(int, modelIndex, "DT_BaseViewModel", "m_nModelIndex")
	NETVAR(Vector, vecOrigin, "DT_BasePlayer", "m_vecOrigin")
	NETVAR(bool, isDefused, "DT_PlantedC4", "m_bBombDefused")

	Vector hitboxPos(int id);
	bool isGrenade();
	bool isC4();
	bool isPlantedC4();
	unsigned char dormant() { return *reinterpret_cast<unsigned char*>(this + 0xED); }
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
	NETVAR(bool, isDefusing, "DT_CSPlayer", "m_bIsDefusing")
	NETVAR(bool, hasDefuseKit, "DT_CSPlayer", "m_bHasDefuser")
	NETVAR(float, flashAlpha, "DT_CSPlayer", "m_flFlashMaxAlpha")
	NETVAR(float, flashDuration, "DT_CSPlayer", "m_flFlashDuration")
	NETVAR(int, shotsFired, "DT_CSPlayer", "m_iShotsFired")
	NETVAR(Vector, velocity, "DT_BasePlayer", "m_vecVelocity[0]")
	NETVAR(bool, hasHelmet, "DT_CSPlayer", "m_bHasHelmet")

	bool isAlive() { return (health() > 0); }
	bool isVisible(const Vector& position);
	void invalidateBoneCache();
	WeaponEntity* activeWeapon();
	
	int moveType() { return *reinterpret_cast<int*>(this + netvars::moveType); } // REDO
	Vector eyePosition()
	{
		Vector v;
		call_virtual_method<void, 285>(this, std::ref(v));
		return v;
	}
	bool isBombCarrier() 
	{
		static auto is_c4_owner{ reinterpret_cast<bool(__thiscall*)(Entity*)>(pattern_scan("client.dll", "56 8B F1 85 F6 74 31")) };
		return is_c4_owner(this);
	}
};

class LocalplayerEntity : public PlayerEntity
{
public:
	NETVAR(unsigned int*, weapons, "DT_CSPlayer", "m_hMyWeapons")
	NETVAR(Vector, aimPunch, "DT_BasePlayer", "m_aimPunchAngle")
	NETVAR(int, viewmodel, "DT_BasePlayer", "m_hViewModel[0]")
	void aimAt(Vector pos, CUserCmd* cmd, bool silent = config::silentAim);
};

class WeaponEntity : public Entity
{
public:
	VIRTUAL_METHOD(WeaponType, weaponType, 455, (), (this))
	VIRTUAL_METHOD(WeaponInfo*, weaponData, 461, (), (this))
	VIRTUAL_METHOD(float, inaccuracy, 483, (), (this))

	NETVAR(int, itemDefIndex, "DT_BaseCombatWeapon", "m_iItemDefinitionIndex")
	NETVAR(int, paintKit, "DT_BaseAttributableItem", "m_nFallbackPaintKit")
	NETVAR(int, quality, "DT_BaseAttributableItem", "m_iEntityQuality")
	NETVAR(float, wear, "DT_BaseAttributableItem", "m_flFallbackWear")
	NETVAR(int, ogOwnerLow, "DT_BaseAttributableItem", "m_OriginalOwnerXuidLow")
	NETVAR(int, ogOwnerHigh, "DT_BaseAttributableItem", "m_OriginalOwnerXuidHigh")
	NETVAR(int, fallbackSeed, "DT_BaseAttributableItem", "m_nFallbackSeed")
	NETVAR(int, itemId, "DT_BaseAttributableItem", "m_iItemIDHigh")
	NETVAR(int, hWorldModel, "DT_BaseCombatWeapon", "m_hWeaponWorldModel")
	NETVAR(float, nextPrimaryAttack, "DT_BaseCombatWeapon", "m_flNextPrimaryAttack")
	
	bool isKnife() { return weaponType() == WeaponType::Knife; }
	bool isPistol() { return weaponType() == WeaponType::Pistol; }
	bool isRevolver() { return (itemDefIndex() == 64 || itemDefIndex() == 262208); }

	std::wstring weaponTypeStr();
};

class ViewmodelEntity : public Entity
{
public:
	NETVAR(int, hWeapon, "DT_BaseViewModel", "m_hWeapon")
};