#pragma once

#include "helper.h"
#include "IMaterial.h"

class IMaterialSystem
{
public:
	VIRTUAL_METHOD(IMaterial*, FindMaterial, 84, (const char* materialName, const char* textureGroupName), (this, materialName, textureGroupName, true, NULL))
	VIRTUAL_METHOD(short, FirstMaterial, 86, (), (this))
	VIRTUAL_METHOD(short, NextMaterial, 87, (short handle), (this, handle))
	VIRTUAL_METHOD(short, InvalidMaterial, 88, (), (this))
	VIRTUAL_METHOD(IMaterial*, GetMaterial, 89, (short handle), (this, handle))
};