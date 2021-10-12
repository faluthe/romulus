#pragma once

#include <Windows.h>

namespace netvars
{
	inline uintptr_t flags;
	inline uintptr_t health;
	inline uintptr_t moveType;
	inline uintptr_t team;
	
	void init();
}