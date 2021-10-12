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
};