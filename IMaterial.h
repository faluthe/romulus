#pragma once

#include "helper.h"

class IMaterial
{
public:
	const char* name()
	{
		return call_virtual_method<const char* (__thiscall*)(void*)>(this, IMAT_NAME)(this);
	}

	const char* textureGroupName()
	{
		return call_virtual_method<const char* (__thiscall*)(void*)>(this, 1)(this);
	}

	void AlphaModulate(float a)
	{
		return call_virtual_method<void(__thiscall*)(void*, float)>(this, IMAT_ALPHAMOD)(this, a);
	}

	void ColorModulate(float r, float g, float b)
	{
		return call_virtual_method<void(__thiscall*)(void*, float, float, float)>(this, IMAT_COLORMOD)(this, r, g, b);
	}

	void SetMaterialVarFlags(int flag, bool on)
	{
		return call_virtual_method<void(__thiscall*)(void*, int, bool)>(this, IMAT_SETMATFLAG)(this, flag, on);
	}

	bool isPrecached()
	{
		return call_virtual_method<bool(__thiscall*)(void*)>(this, 70)(this);
	}
};