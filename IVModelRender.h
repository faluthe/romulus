#pragma once

#include "helper.h"
#include "IMaterial.h"

struct model_t
{
	void* fnHandle;
	char name[260];
};

struct ModelRenderInfo_t
{
	char pad0[32];
	const model_t* pModel;
	char pad1[16];
	int entityIndex;
};

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