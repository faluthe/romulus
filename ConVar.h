#pragma once

#include "helper.h"

class ConVar
{
public:
	char pad0[12];
	const char* name;

	float GetFloat()
	{
		return call_virtual_method<float(__thiscall*)(void*)>(this, CONVAR_GETFLOAT)(this);
	}

	int GetValue()
	{
		return call_virtual_method<int(__thiscall*)(void*)>(this, CONVAR_GETVALUE)(this);
	}

	void SetFloat(float newValue)
	{
		return call_virtual_method<void(__thiscall*)(void*, float)>(this, CONVAR_SETFLOAT)(this, newValue);
	}

	void SetValue(int newValue)
	{
		return call_virtual_method<void(__thiscall*)(void*, int)>(this, CONVAR_SETVALUE)(this, newValue);
	}
};