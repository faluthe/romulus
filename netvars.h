#pragma once

#include <Windows.h>

namespace netvars
{
	inline uintptr_t activeWeapon{};
	inline uintptr_t aimPunch{};
	inline uintptr_t armor{};
	inline uintptr_t c4Blow{};
	inline uintptr_t flags{};
	inline uintptr_t health{};
	inline uintptr_t isScoped{};
	inline uintptr_t itemDefIndex{};
	inline uintptr_t moveType{};
	inline uintptr_t nextPrimaryAttack{};
	inline uintptr_t simulationTime{};
	inline uintptr_t team{};
	inline uintptr_t tickBase{};
	inline uintptr_t vecOrigin{};
	
	void init();
}