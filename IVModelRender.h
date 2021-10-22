#pragma once

#include "helper.h"

class IMaterial;

class IVModelRender
{
public:
	void ForcedMaterialOverride(IMaterial* material)
	{
		return call_virtual_method<void(__thiscall*)(void*, IMaterial*, int, int)>(this, MDLRENDER_FORCEMATOVERIDE)(this, material, 0, 0);
	}

	bool IsForcedMaterialOverride()
	{
		return call_virtual_method<bool(__thiscall*)(void*)>(this, MDLRENDER_ISFORCEDMAT)(this);
	}
};