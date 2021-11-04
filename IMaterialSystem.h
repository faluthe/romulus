#pragma once

#include "helper.h"
#include "IMaterial.h"

class IMaterialSystem
{
public:
	IMaterial* FindMaterial(const char* matName, const char* textureGroupName)
	{
		return call_virtual_method<IMaterial* (__thiscall*)(void*, const char*, const char*, bool, const char*)>(this, IMATSYS_FINDMAT)(this, matName, textureGroupName, true, NULL);
	}

	short firstMat()
	{
		return call_virtual_method<short(__thiscall*)(void*)>(this, 86)(this);
	}

	short nextMat(short handle)
	{
		return call_virtual_method<short(__thiscall*)(void*, short)>(this, 87)(this, handle);
	}

	short invalidMat()
	{
		return call_virtual_method<short(__thiscall*)(void*)>(this, 88)(this);
	}

	IMaterial* GetMaterial(short handle)
	{
		return call_virtual_method<IMaterial* (__thiscall*)(void*, short)>(this, 89)(this, handle);
	}
};