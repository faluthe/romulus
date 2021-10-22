#pragma once

#include "helper.h"
#include "structs.h"

class IVModelInfo
{
public:
	studiohdr_t* GetStudioModel(const model_t* model)
	{
		return call_virtual_method<studiohdr_t* (__thiscall*)(void*, const model_t*)>(this, MDLINFO_GETSTUDIO)(this, model);
	}
};