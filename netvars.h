#pragma once

#include <Windows.h>

namespace netvars
{
	inline uintptr_t activeWeapon{};
	inline uintptr_t aimPunch{};
	inline uintptr_t armor{};
	inline uintptr_t c4Blow{};
	inline uintptr_t entQuality{};
	inline uintptr_t fallbackSeed{};
	inline uintptr_t fallbackWear{};
	inline uintptr_t flags{};
	inline uintptr_t gunGameImmunity{};
	inline uintptr_t health{};
	inline uintptr_t isScoped{};
	inline uintptr_t itemDefIndex{};
	inline uintptr_t itemId{};
	inline uintptr_t modelIndex{};
	inline uintptr_t moveType{};
	inline uintptr_t myWeapons{};
	inline uintptr_t nextPrimaryAttack{};
	inline uintptr_t originalOwnerLow{};
	inline uintptr_t originalOwnerHigh{};
	inline uintptr_t paintkit{};
	inline uintptr_t simulationTime{};
	inline uintptr_t team{};
	inline uintptr_t tickBase{};
	inline uintptr_t vecOrigin{};
	inline uintptr_t viewmodel{};
	inline uintptr_t viewmodelWeapon{};
	inline uintptr_t viewmodelModelIndex{};
	inline uintptr_t worldModel{};

	void init();
}

uintptr_t get_netvar(const char* tableName, const char* netvarName);

#define NETVAR(type, functionName, table, prop) \
type& functionName() \
{ \
	static uintptr_t offset = 0; \
	if (!offset) { offset = get_netvar(table, prop); } \
	\
	return *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(this) + offset); \
}