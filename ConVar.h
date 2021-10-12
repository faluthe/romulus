#pragma once

#include "helper.h"

class ConVar
{
public:
	char pad0[12];
	const char* name;

	int GetValue()
	{
		return call_virtual_method<int(__thiscall*)(void*)>(this, CONVAR_GETVALUE)(this);
	}

	void SetValue(int newValue)
	{
		return call_virtual_method<void(__thiscall*)(void*, int)>(this, CONVAR_SETVALUE)(this, newValue);
	}
};