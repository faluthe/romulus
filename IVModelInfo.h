#pragma once

#include "helper.h"
#include "structs.h"

class IVModelInfo
{
public:
	VIRTUAL_METHOD(model_t*, GetModel, 1, (int modelIndex), (this, modelIndex))
	VIRTUAL_METHOD(int, GetModelIndex, 2, (const char* filename), (this, filename))
	VIRTUAL_METHOD(const char*, GetModelName, 3, (const model_t* model), (this, model))
	VIRTUAL_METHOD(studiohdr_t*, GetStudioModel, 32, (const model_t* model), (this, model))
};