#pragma once

#include "helper.h"

class IMaterial;

class IVModelRender
{
public:
	VIRTUAL_METHOD(void, ForcedMaterialOverride, 1, (IMaterial* material), (this, material, 0, 0))
	VIRTUAL_METHOD(bool, IsForcedMaterialOverride, 2, (), (this))
};